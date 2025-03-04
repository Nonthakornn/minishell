#include "minishell.h"

void free_redirects(t_redirect *head)
{
	t_redirect	*tmp;

	tmp = NULL;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_process_and_redir(t_process *head)
{
	int		i;
	t_process *tmp;

	while (head)
	{
		i = 0;
		tmp = head;
		head = head->next;
		while (tmp->cmd[i])
			free(tmp->cmd[i++]);
		free(tmp->cmd);
		if (tmp->redirect)
			free_redirects(tmp->redirect);
		if (tmp->pipe_in)
			free(tmp->pipe_in);
		if (tmp->here_doc)
			free(tmp->here_doc);
		free(tmp);
	}
}

void	close_fd(t_process *head)
{
	int	i;

	while (head)
	{
		if (head->pipe_in)
		{
			close((head->pipe_in)[0]);
			close((head->pipe_in)[1]);
		}
		if (head->here_doc)
		{
			i = 0;
			while ((head->here_doc)[i])
			{
				close((head->here_doc)[i]);
				i++;
			}
		}
		head = head->next;
	}
}
