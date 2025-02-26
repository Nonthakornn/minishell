#include "minishell.h"

int	read_file_in_pipe(t_redirect *redir)
{
	int	fd;

	fd = 0;
	while (redir)
	{
		if (redir->token_type == READ_FILE)
		{
			if (fd > 2)
				close(fd);
			fd = open(redir->value, O_RDONLY);
			if (fd < 0)
				return (-1);
		}
		redir = redir->next;
	}
	return fd;
}

int	get_last_token_type(t_redirect *redir)
{
	int	type;

	type = 0;
	while(redir)
	{
		type = redir->token_type;
		redir = redir->next;
	}
	return type;
}

// int	redirect_in_pipe(t_redirect *redir, int here_doc_fd)
// {
// 	int			file_fd;
// 	t_redirect	*temp;
// 	int			last_token_type;

// 	file_fd = read_file_in_pipe(redir);
// 	if (file_fd < 0)
// 		return (-1);
// 	last_token_type = get_last_token_type(redir);
// 	if (last_token_type == READ_FILE)
// 	{
// 		if (dup2(file_fd, STDIN_FILENO) == -1)
// 			return (-1);
// 		if (file_fd > 2)
// 			close(file_fd);
// 		return (1);
// 	}
// 	if (last_token_type == HERE_DOC)
// 	{
// 		if (dup2(here_doc_fd, STDIN_FILENO) == -1)
// 			return (-1);
// 		if (file_fd > 2)
// 			close(file_fd);
// 		return (1);
// 	}
// 	return (0);
// }

int	redirect_in_pipe(t_redirect *redir, int *here_doc_fd)
{
	int	offset;
	int	infile_fd;
	int	outfile_fd;

	infile_fd = -1;
	outfile_fd = -1;
	while (redir)
	{
		offset = 0;
		if (redir->token_type == READ_FILE)
		{
			if (infile_fd > 2)
				close(infile_fd);
			infile_fd = open(redir->value, O_RDONLY);
			if (infile_fd  < 0)
				return (-1);
		}
		if (redir->token_type == HERE_DOC)
		{
			if (infile_fd > 2)
				close(infile_fd);
			infile_fd = here_doc_fd[offset];
			offset++;
		}
		if (redir->token_type == WRITE_FILE)
		{
			if (outfile_fd > 2)
				close(outfile_fd);
			outfile_fd = open(redir->value, O_CREAT | O_TRUNC);
		}
		redir = redir->next;
	}
	if (infile_fd > 2)
	{
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
	}
	if (outfile_fd > 2)
	{
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
	}
	return (0);
}
