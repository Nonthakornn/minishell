#include "minishell.h"

static void	init_store(t_redir_store *store, t_process *process)
{
	store->offset = 0;
	store->infile_fd = -1;
	store->outfile_fd = -1;
	store->cur_infile_type = -1;
	if (process->pipe_in)
		dup2((process->pipe_in)[0], STDIN_FILENO);
	if (process->pipe_out)
		dup2((process->pipe_out)[1], STDOUT_FILENO);
}

static void	std_redirect(t_redir_store *store)
{
	if (store->infile_fd > 2)
	{
		dup2(store->infile_fd, STDIN_FILENO);
		if (store->cur_infile_type == READ_FILE)
			close(store->infile_fd);
	}
	if (store->outfile_fd > 2)
	{
		dup2(store->outfile_fd, STDOUT_FILENO);
		close(store->outfile_fd);
	}
}

static int	process_readfile(t_redir_store *store, \
	t_redirect *redir, int *heredoc)
{
	if (store->infile_fd > 2 && store->cur_infile_type == READ_FILE)
		close(store->infile_fd);
	if (redir->token_type == READ_FILE)
	{
		store->cur_infile_type = READ_FILE;
		store->infile_fd = open(redir->value, O_RDONLY);
	}
	if (redir->token_type == HERE_DOC)
	{
		store->cur_infile_type = HERE_DOC;
		store->infile_fd = heredoc[store->offset];
		store->offset = store->offset + 1;
	}
	if (store->infile_fd < 0)
	{
		error_access(redir->value);
		return (-1);
	}
	return (0);
}

static int	process_writefile(t_redir_store *store, t_redirect *redir)
{
	if (store->outfile_fd > 2)
		close(store->outfile_fd);
	if (redir->token_type == WRITE_FILE)
	{
		store->outfile_fd = open(redir->value, O_CREAT | O_TRUNC | O_WRONLY, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	if (redir->token_type == APPEND_FILE)
	{
		store->outfile_fd = open(redir->value, O_CREAT | O_APPEND | O_WRONLY, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	if (store->outfile_fd < 0)
	{
		error_access(redir->value);
		return (-1);
	}
	return (0);
}

int	process_redirect(t_process *process)
{
	t_redir_store	store;
	t_redirect		*redir;
	int				*heredoc;

	redir = process->redirect;
	heredoc = process->here_doc;
	init_store(&store, process);
	while (redir)
	{
		if (redir->token_type == READ_FILE || redir->token_type == HERE_DOC)
		{
			if (process_readfile(&store, redir, heredoc) == -1)
				return (1);
		}
		if (redir->token_type == WRITE_FILE || redir->token_type == APPEND_FILE)
		{
			if (process_writefile(&store, redir) == -1)
				return (1);
		}
		redir = redir->next;
	}
	std_redirect(&store);
	return (0);
}
