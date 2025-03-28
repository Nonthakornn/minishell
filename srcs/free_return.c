#include "minishell.h"

t_token	*free_token_return(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
	printf("Syntax Error: Unclose quote\n");
	return (NULL);
}

void	free_everything(t_process *proc, char **var, int std[2])
{
	recover_stdfd(std);
	close_pipe(proc);
	free_process_and_redir(proc);
	free_str_arr(var);
}
