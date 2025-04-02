#include "minishell.h"

static int	count_heredoc_in_process(t_redirect *redir)
{
	int	count;

	count = 0;
	while (redir)
	{
		if (redir->token_type == HERE_DOC)
			count++;
		redir = redir->next;
	}
	return (count);
}

static int	*exec_heredoc_in_process(t_redirect *redir)
{
	int	*fds;
	int	redir_number;
	int	i;

	i = 0;
	redir_number = count_heredoc_in_process(redir);
	fds = malloc(sizeof(int) * (redir_number + 1));
	fds[redir_number] = 0;
	while (redir)
	{
		if (redir->token_type == HERE_DOC)
		{
			fds[i] = input_heredoc(redir->value);
			i++;
		}
		redir = redir->next;
	}
	return (fds);
}

void	exec_heredoc(t_process *process)
{
	while (process)
	{
		process->here_doc = exec_heredoc_in_process(process->redirect);
		process = process->next;
	}
}
