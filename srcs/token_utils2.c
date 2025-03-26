#include "minishell.h"

char	*create_quoted_string(char *str, int start, int end)
{
	char	*word;
	int		len;
	int		j;

	len = end - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (j < len)
	{
		word[j] = str[start + j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

char	*extract_quote(char *str, int *i, char quote_char)
{
	int	start;

	start = *i;
	if (str[*i] == quote_char)
		return (create_empty_string());
	while (str[*i] && str[*i] != quote_char)
		(*i)++;
	if (str[*i] == quote_char)
		return (create_quoted_string(str, start, *i));
	return (NULL);
}

int	join_with_previous(t_token **head, char *word)
{
	t_token	*last;
	char	*combined;

	if (!*head)
		return (0);
	last = lastnode_token_lst(*head);
	if (!last || last->token_type != CMD)
		return (0);
	combined = malloc(ft_strlen(last->value) + ft_strlen(word) + 1);
	if (!combined)
		return (0);
	ft_strcpy(combined, last->value);
	ft_strcat(combined, word);
	free(last->value);
	last->value = combined;
	return (1);
}

t_token	*process_quoted_word(char *word, t_quote_state quote_type)
{
	t_token	*new_token;

	new_token = create_token_lst(CMD, word);
	new_token->quote_type = quote_type;
	return (new_token);
}

char	*extract_normal_word(char *str, int *i, int *len)
{
	char	*word;
	int		start;
	int		j;

	start = *i;
	while (str[*i] && is_normal_char(str[*i]))
		(*i)++;
	*len = *i - start;
	word = malloc(*len + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (j < *len)
	{
		word[j] = str[start + j];
		j++;
	}
	word[j] = '\0';
	return (word);
}
