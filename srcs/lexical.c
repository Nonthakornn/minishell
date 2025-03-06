#include "minishell.h"

t_token	*tokenize(char *input)
{
	int				i;
	t_token			*head;
	t_quote_state	state;
	int				start;
	char			*word;

	i = 0;
	head = NULL;
	state = NORMAL;
	while (input[i])
	{
		if (state == NORMAL && is_space(input[i]))
		{
			i++;
			continue;
		}
		//Handle operator in NORMAL STATE
		if (state == NORMAL)
		{
			if (input[i] == '|')
			{
				addback_token_lst(&head, create_token_lst(PIPE, "|"));
				i++;
				continue;
			}
			else if (input[i] == '<' && input[i + 1] == '<')
			{
				addback_token_lst(&head, create_token_lst(HERE_DOC, "<<"));
				i+=2;
				continue;
			}
			else if (input[i] == '>' && input[i + 1] == '>')
			{
				addback_token_lst(&head, create_token_lst(APPEND_FILE, ">>"));
				i+=2;
				continue;
			}
			else if (input[i] == '<')
			{
				addback_token_lst(&head, create_token_lst(READ_FILE, "<"));
				i++;
				continue;
			}
			else if (input[i] == '>')
			{
				addback_token_lst(&head, create_token_lst(WRITE_FILE, ">"));
				i++;
				continue;
			}
		}
		//Handle quotes
		if ((input[i] == '\'' || input[i] == '\"') && state == NORMAL)
		{
			char quote_char;

			quote_char = input[i];
			if (quote_char == '\'')
				state = SINGLE_QUOTE;
			else
				state = DOUBLE_QUOTE;
			start = i;
			i++; //skip opening quote
			//Find closing quote
			while (input[i] && input[i] != quote_char)
				i++;
			if (input[i] == quote_char)
			{
				int len = i - start - 1;
				int j = 0;
				word = malloc(len + 1);
				while (j < len)
				{
					word[j] = input[start + j + 1];
					j++;
				}
				word[j] = '\0';
				addback_token_lst(&head, create_token_lst(CMD, word));
				free(word);
				i++;
				state = NORMAL;
				continue;
			}
			else
				break;
		}
		if (state == NORMAL)
		{
			start = i;
			while (input[i] && !is_space(input[i]) &&
				input[i] != '|' && input[i] != '<' && input[i] != '>' &&
				input[i] != '\'' && input[i] != '\"')
				i++;
			if (i > start)
			{
				int len = i - start;
				int j = 0;
				word = malloc(len + 1);
				while (j < len)
				{
					word[j] = input[start + j];
					j++;
				}
				word[j] = '\0';
				addback_token_lst(&head, create_token_lst(CMD, word));
				free(word);
				continue;
			}
		}
		else
			i++;
	}
	if (state != NORMAL)
	{
		printf(RED"Check your quote propery!\n"RST);
		return (head);
	}
	return (head);
}
