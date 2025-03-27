#include "minishell.h"

static void	remove_token(t_token **head, t_token *prev,
	t_token *current, t_token *next)
{
	if (prev)
		prev->next = next;
	else
		*head = next;
	free(current->value);
	free(current);
}

static void	update_token_value(t_token *current, char *expanded_value)
{
	if (expanded_value != current->value)
	{
		free(current->value);
		current->value = expanded_value;
	}
}

/*
Handle CMD token processing
returns -> 1 if prev should be updated 0 if not
*/
static int	handle_cmd_expression(t_token **head, t_token *prev,
	t_token *current, char **variable)
{
	char	*expanded_value;

	if (current->quote_type == SINGLE_QUOTE)
		return (1);
	expanded_value = handle_dollar(current->value, variable);
	if (expanded_value != NULL && expanded_value[0] == '\0')
	{
		if (expanded_value != current->value)
			free(expanded_value);
		remove_token(head, prev, current, current->next);
		return (0);
	}
	update_token_value(current, expanded_value);
	return (1);
}

bool	expand_token(t_token **token, char **variable)
{
	t_token	*head;
	t_token	*current;
	t_token	*prev;
	t_token	*next;

	head = *token;
	prev = NULL;
	next = NULL;
	current = head;
	while (current)
	{
		next = current->next;
		if (current->token_type == CMD)
		{
			if (handle_cmd_expression(&head, prev, current, variable))
				prev = current;
		}
		else
			prev = current;
		current = next;
	}
	*token = head;
	if (head == NULL)
		return (false);
	return (true);
}
