#include "minishell.h"

static char *handle_dollar(char *str, char **variable)
{
	char	*behind_dollar;
	int		i;
	int 	count;
	int		var_index;
	char	*var_value;
	char	*temp;

	i = 0;
	count = 0;
	var_index = 0;
	behind_dollar = NULL;
	temp = NULL;
	while (is_space(str[i]))
		i++;
	if (str[i] == '$' && !(str[i + 1]))
		return (str);
	if (str[i] == '$')
	{
		i++;
		count = i;
		while (str[count])
			count++;
		behind_dollar = malloc(count + 2); //For && NULL
		count = 0;
		while (str[i])
			behind_dollar[count++] = str[i++];
		behind_dollar[count] = '=';
		behind_dollar[count + 1] = '\0';

		var_index = (get_variable_index(variable, behind_dollar));
		printf("Behind Dollar: %s\n", behind_dollar);
		printf("variable index: %d\n", var_index);

		if (var_index != - 1)
		{
			var_value = ft_strchr(variable[var_index], '=');
			if (var_value)
			{
				var_value++;
				temp = ft_strdup(var_value);
				if (temp)
				{
					printf("value: %s\n", temp);
					free(behind_dollar);
					return (temp);
				}
			}
			return (temp);
		}
	}
	return (str);
}

void expand_token(t_token **token, char **variable)
{
	t_token *head;

	head = *token;
	print_str_arr(variable);
	while ((*token))
	{
		if ((*token)->token_type == CMD)
		{
			(*token)->value = handle_dollar((*token)->value, variable);
		}
		(*token) = (*token)->next;
	}
	(*token) = head;
}