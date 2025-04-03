#include "minishell.h"

int	ft_combine(t_token *last, char *word)
{
	char	*combined;

	combined = malloc(ft_strlen(last->value) + ft_strlen(word) + 1);
	if (!combined)
		return (0);
	ft_strcpy(combined, last->value);
	ft_strcat(combined, word);
	free(last->value);
	last->value = combined;
	free(word);
	return (1);
}

int	check_quote_and_state(char *str, int i, t_quote_state state)
{
	return ((str[i] == '\'' || str[i] == '\"') && state == NORMAL);
}

/*
hello'world' - minus 2 quote and 
checks if there was a space before the opening quote
*/
int	is_ok_to_join(char *str, int i, char *word)
{
	int	pos_before_quote;

	pos_before_quote = i - ft_strlen(word) - 2;
	return (i > 1 && pos_before_quote >= 0
		&& !is_space(str[pos_before_quote]));
}

t_quote_state	assign_quote_type(char quote_char)
{
	if (quote_char == '\'')
		return (SINGLE_QUOTE);
	else
		return (DOUBLE_QUOTE);
}

bool	process_token(t_token **tokens, char **var)
{
	if (!expand_token(tokens, var))
	{
		free_token(*tokens);
		return (false);
	}
	if (!check_syntax_err(*tokens))
	{
		g_signal = 2;
		print_str(2, "Syntax Error");
		free_token(*tokens);
		return (false);
	}
	return (true);
}
