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

void	free_pipe_and_redir(t_pipe *head)
{
	int		i;
	t_pipe *tmp;

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
		free(tmp);
	}
}
