#include "minishell.h"

t_token	*create_token_lst(t_token_type type, char *value)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->token_type = type;
	new_node->value = malloc(ft_strlen(value) + 1);
	if (!new_node->value)
	{
		free(new_node);
		return (NULL);
	}
	strcpy(new_node->value, value);
	new_node->next = NULL;
	return (new_node);
}

t_token	*lastnode_token_lst(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return (NULL);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	addback_token_lst(t_token **head, t_token *new_node)
{
	if (!head || !new_node)
		return ;
	if (!(*head))
		*head = new_node;
	else
		lastnode_token_lst(*head)->next = new_node;
}

void	display_token_lst(t_token *head)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = head;
	if (!head)
		return ;
	printf(CYAN"Token List:\n"RST);
	while (tmp)
	{
		printf("Token[%d]:\n", i);
		printf(" Type: %s\n", get_str_token(tmp->token_type));
		printf(" Value: \"%s\"\n", tmp->value);
		tmp = tmp->next;
		i++;
	}
	printf(CYAN"----------------------------\n"RST);
}
