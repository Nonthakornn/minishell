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
