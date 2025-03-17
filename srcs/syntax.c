#include "minishell.h"

static bool	check_redir_type(t_token *tokens)
{
	return ((tokens->token_type == READ_FILE || tokens->token_type == HERE_DOC
			|| tokens->token_type == WRITE_FILE
			|| tokens->token_type == APPEND_FILE));
}

static bool	check_pipe_err(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (temp->token_type == PIPE)
		return (false);
	while (temp->next)
	{
		if (temp->token_type == PIPE && temp->next->token_type == PIPE)
			return (false);
		temp = temp->next;
	}
	if (temp->token_type == PIPE)
		return (false);
	return (true);
}

static bool	check_redirection_err(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (check_redir_type(temp))
		{
			if (!temp->next)
				return (false);
			if (check_redir_type(temp->next))
				return (false);
			if (temp->next->token_type != CMD)
				return (false);
		}
		temp = temp->next;
	}
	return (true);
}

bool	check_syntax_err(t_token *tokens)
{
	if (!check_pipe_err(tokens))
		return (false);
	if (!check_redirection_err(tokens))
		return (false);
	return (true);
}

t_process	*syntax(t_token *tokens)
{
	t_token		*tmp;
	t_process	*head;
	char		**cmd;
	int			count;
	int			i;

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
