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

int	handle_quote(char *str, int *i, t_token **head, t_quote_state *state)
{
	char	quote_char;
	char	*word;

	word = NULL;
	if ((str[*i] == '\'' || str[*i] == '\"') && *state == NORMAL)
	{
		quote_char = str[*i];
		if (quote_char == '\'')
			*state = SINGLE_QUOTE;
		else
			*state = DOUBLE_QUOTE;
		(*i)++ ;
		word = extract_quote(str, i, quote_char);
		if (word)
		{
			addback_token_lst(head, create_token_lst(CMD, word));
			free(word);
			(*i)++;
			*state = NORMAL;
		}
		return (1);
	}
	return (0);
}

int	handle_normal_word(char *str, int *i, t_token **head)
{
	char	*word;
	int		start;
	int		len;
	int		j;

	word = NULL;
	start = *i;
	len = 0;
	j = 0;
	while (str[*i] && !is_space(str[*i]) && str[*i] != '|'
		&& str[*i] != '>' && str[*i] != '<' && str[*i] != '\''
		&& str[*i] != '\"')
		(*i)++ ;
	len = *i - start;
	word = malloc(len + 1);
	while (j < len)
	{
		word[j] = str[start + j];
		j++;
	}
	word[j] = '\0';
	addback_token_lst(head, create_token_lst(CMD, word));
	free(word);
	return (1);
}
