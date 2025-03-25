#include "minishell.h"

static char	*extract_quote(char *str, int *i, char quote_char)
{
	char	*word;
	int		start;
	int		len;
	int		j;

	word = NULL;
	len = 0;
	j = 0;
	start = *i;
	while (str[*i] && str[*i] != quote_char)
		(*i)++;
	if (str[*i] == quote_char)
	{
		len = *i - start;
		word = malloc(len + 1);
		while (j < len)
		{
			word[j] = str[start + j];
			j++;
		}
		word[j] = '\0';
		return (word);
	}
	return (NULL);
}

static t_token	*process_quoted_word(char *word, t_quote_state quote_type)
{
	t_token	*new_token;

	new_token = create_token_lst(CMD, word);
	new_token->quote_type = quote_type;
	return (new_token);
}

int	handle_quote(char *str, int *i, t_token **head, t_quote_state *state)
{
	char			quote_char;
	char			*word;
	t_quote_state	quote_type;

	if ((str[*i] == '\'' || str[*i] == '\"') && *state == NORMAL)
	{
		quote_char = str[*i];
		if (quote_char == '\'')
			quote_type = SINGLE_QUOTE;
		else
			quote_type = DOUBLE_QUOTE;
		*state = quote_type;
		(*i)++;
		word = extract_quote(str, i, quote_char);
		if (word)
		{
			addback_token_lst(head, process_quoted_word(word, quote_type));
			free(word);
			(*i)++;
			*state = NORMAL;
			return (1);
		}
	}
	return (0);
}

int	handle_normal_word(char *str, int *i, t_token **head)
{
	char	*word;
	int		start;
	int		len;
	int		j;
	t_token	*new_token;

	word = NULL;
	start = *i;
	len = 0;
	j = 0;
	while (str[*i] && is_normal_char(str[*i]))
		(*i)++ ;
	len = *i - start;
	word = malloc(len + 1);
	while (j < len)
	{
		word[j] = str[start + j];
		j++;
	}
	word[j] = '\0';
	new_token = create_token_lst(CMD, word);
	new_token->quote_type = NORMAL;
	addback_token_lst(head, new_token);
	free(word);
	return (1);
}
