#include "minishell.h"

static int valid_to_expand(char *result, int i)
{
	return (result[i] == '$' && result[i + 1]
			&& (ft_isalnum(result[i + 1])
			|| result[i + 1] == '_'));
}

static char *handle_dollar(char *str, char **variable)
{
	char	*result;
	int		i;
	int		var_start;
	int		var_end;
	char	*var_name;
	int		var_index;
	char	*var_value;

	//return original string if no $
	if (!ft_strchr(str, '$'))
		return (str);
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
	{
		if (valid_to_expand(result, i))
		{
			var_start = i;
			i++; // skip $
			var_end = i;
			while (result[var_end] && (ft_isalnum(result[var_end]) || result[var_end] == '_'))
				var_end++;
			var_name = ft_substr(result, i, var_end - 1);
			if (!var_name)
				return (result);
			var_index = get_variable_index(variable, var_name);
			printf("Variable name: %s\n", var_name);
			printf("Variable index: %d\n", var_index);

			if (var_index != -1)
			{
				var_value = ft_strchr(variable[var_index], '=');
				if (var_value)
				{
					var_value++; // skip '=;
					char *before = ft_substr(result, 0, var_start);
                    char *after = ft_strdup(result + var_end);
                    char *temp = str_join(before, var_value);
                    char *new_result = str_join(temp, after);
                    free(before);
                    free(after);
                    free(temp);
                    free(result);
                    result = new_result;
                    i = var_start + ft_strlen(var_value) - 1; // Adjust position
				}
			}
			else
			{
				char *before = ft_substr(result, 0, var_start);
				char *after = ft_strdup(result + var_end);
				char *new_result = str_join(before, after);
				free(before);
				free(after);
				free(result);
				result = new_result;
				i = var_start - 1; // Adjust position
			}
			free(var_name);
		}
		i++;
	}
	return (result);
}

void expand_token(t_token **token, char **variable)
{
	t_token *head;
	// t_token	*current;
	// t_token	*token;

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