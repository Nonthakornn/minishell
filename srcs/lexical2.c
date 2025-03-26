#include "minishell.h"

static int	process_quoted_token(t_token **head, char *word,
				t_quote_state quote_type, int *i);

int	handle_normal_word(char *str, int *i, t_token **head)
{
	char	*word;
	int		start;
	int		len;
	t_token	*new_token;
	t_token	*last;

	start = *i;
	word = extract_normal_word(str, i, &len);
	if (!word)
		return (0);
	if (start > 0 && !is_space(str[start - 1]) && *head)
	{
		last = lastnode_token_lst(*head);
		if (last && last->token_type == CMD)
			return (ft_combine(last, word));
	}
	new_token = create_token_lst(CMD, word);
	new_token->quote_type = NORMAL;
	addback_token_lst(head, new_token);
	free(word);
	return (1);
}

int	handle_quote(char *str, int *i, t_token **head, t_quote_state *state)
{
	char			quote_char;
	char			*word;
	t_quote_state	quote_type;

	if (check_quote_and_state(str, *i, *state))
	{
		quote_char = str[*i];
		quote_type = assign_quote_type(quote_char);
		*state = quote_type;
		(*i)++;
		word = extract_quote(str, i, quote_char);
		if (word)
		{
			if (is_ok_to_join(str, *i, word))
				process_quoted_token(head, word, quote_type, i);
			else
			{
				addback_token_lst(head, process_quoted_word(word, quote_type));
				(*i)++;
			}
			*state = NORMAL;
			return (1);
		}
	}
	return (0);
}

static int	process_quoted_token(t_token **head, char *word,
	t_quote_state quote_type, int *i)
{
	int	joined;

	joined = join_with_previous(head, word);
	if (!joined)
		addback_token_lst(head, process_quoted_word(word, quote_type));
	else
		free(word);
	(*i)++;
	return (1);
}


/*
handle_quote Flow
Is this a quote character and are we in NORMAL state?
	No -> Return 0 (no quote handled)
	yes:
		1. Set quote_char to current character
		2. Determine quote_type (SINGLE_QUOTE or DOUBLE_QUOTE)
		3. Update state to the quote_type
		4. Move to next character (i++)
		5. Extract quoted content into 'word'
		6. Was extraction successful?
			No -> Return 0 (extraction failed)
			Yes:
			Should this be joined with previous token?
			Yes -> Process quoted token (join with previous)
			No -> Add as new token and move to next character
	Reset state to NORMAL
     │
     └─ Return 1 (successfully handled quote)
End handle_quote
*/