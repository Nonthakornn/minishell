#include "minishell.h"

void free_token_return(t_token *head) 
{
	t_token *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
	printf("Quote Error\n");
	return ;
}
