#include "minishell.h"

t_process	*syntax(t_token *tokens)
{
	t_token		*tmp;
	t_process	*head;
	char		**cmd;
	int			count;
	int 		i;

	head = NULL;
	cmd = NULL;
	count = 0;
	i = 0;
	tmp = tokens;
	while (tmp && tmp->token_type == CMD)
	{
		count++;
		tmp = tmp->next;
	}
	cmd = malloc(sizeof(char *) * (count + 1));
	tmp = tokens;
	while (i < count && tmp)
	{
		cmd[i] = ft_slice(tmp->value, 0, ft_strlen(tmp->value));
		tmp = tmp->next;
		i++;
	}
	cmd[i] = NULL;
	addback_process_lst(&head, create_process_lst(cmd, NULL));
	return (head);
}
