#include "minishell.h"

bool	check_redir_type(t_token *tokens)
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
