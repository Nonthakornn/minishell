#include "minishell.h"

void	display_redir_lst(t_redirect *head)
{
	int	i;

	i = 0;
	printf(CYAN"Redirection List:\n"RST);
	printf(CYAN"-----------------------------\n"RST);
	if (!head)
		printf(RED"Empty Redirect List!\n"RST);
	while (head)
	{
		printf("Node:%d\n", i);
		printf("type: %s \n", get_str_token(head->token_type));
		printf("value: \"%s\"\n", head->value);
		head = head->next;
		i++;
	}
	printf(CYAN"-----------------------------\n"RST);
}

t_redirect	*create_redir_lst(t_token_type type, char *value)
{
	t_redirect	*new_node;

	new_node = malloc(sizeof(t_redirect));
	if (!new_node)
		return (NULL);
	new_node->token_type = type;
	new_node->value = malloc(ft_strlen(value) + 1);
	if (!new_node->value)
	{
		free(new_node);
		return (NULL);
	}
	ft_strcpy(new_node->value, value);
	new_node->next = NULL;
	return (new_node);
}

t_redirect *lastnode_redir_lst(t_redirect *head)
{
	t_redirect	*ptr;

	if (!head)
		return (NULL);
	ptr = head;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void	addback_redir_lst(t_redirect **head, t_redirect *new_node)
{
	if (!head || !new_node)
		return ;
	if (!(*head))
		*head = new_node;
	else
		lastnode_redir_lst(*head)->next = new_node;
}