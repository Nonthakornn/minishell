#include "minishell.h"

int	**get_hdpipe()
{
	static int	*hdpipe_fd;

	return (&hdpipe_fd);
}

static void	set_hdpipe(int *fds)
{
	int	**hdpipe_fd;

	hdpipe_fd = get_hdpipe();
	*hdpipe_fd= fds;
}

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
	fds = new_int_array(redir_number + 1);
	set_hdpipe(fds);
	while (redir && g_signal == 0)
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
	while (process && g_signal == 0)
	{
		process->here_doc = exec_heredoc_in_process(process->redirect);
		process = process->next;
	}
}
