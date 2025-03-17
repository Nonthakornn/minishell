#include "minishell.h"

static int	handle_pipe(char *str, int *i, t_token **head)
{
	if (str[*i] == '|')
	{
		addback_token_lst(head, create_token_lst(PIPE, "|"));
		(*i)++ ;
		return (1);
	}
	return (0);
}

static int	handle_redirect_in(char *str, int *i, t_token **head)
{
	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		addback_token_lst(head, create_token_lst(HERE_DOC, "<<"));
		(*i) += 2 ;
		return (1);
	}
	else if (str[*i] == '<')
	{
		addback_token_lst(head, create_token_lst(READ_FILE, "<"));
		(*i)++;
		return (1);
	}
	return (0);
}

static int	handle_redirect_out(char *str, int *i, t_token **head)
{
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		addback_token_lst(head, create_token_lst(APPEND_FILE, ">>"));
		(*i) += 2 ;
		return (1);
	}
	else if (str[*i] == '>')
	{
		addback_token_lst(head, create_token_lst(WRITE_FILE, ">"));
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_operator(char *str, int *i, t_token **head)
{
	if (handle_pipe(str, i, head))
		return (1);
	if (handle_redirect_in(str, i, head))
		return (1);
	if (handle_redirect_out(str, i, head))
		return (1);
	return (0);
}

t_token	*tokenize(char *input)
{
	int				i;
	t_token			*head;
	t_quote_state	state;

	i = 0;
	head = NULL;
	state = NORMAL;
	while (input[i])
	{
		if (state == NORMAL && is_space(input[i]))
			i++;
		else if (state == NORMAL && handle_operator(input, &i, &head))
			continue ;
		else if (handle_quote(input, &i, &head, &state))
			continue ;
		else if (state == NORMAL && handle_normal_word(input, &i, &head))
			continue ;
		else
			i++;
	}
	if (state != NORMAL)
		free_token_return(head);
	return (head);
}
