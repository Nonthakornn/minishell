#include "minishell.h"

static char	*extract_var_name(char *str, int start, int *end)
{
	int	var_end;

	var_end = start;
	while (str[var_end] && (ft_isalnum(str[var_end]) || str[var_end] == '_'))
		var_end++;
	*end = var_end;
	return (ft_substr(str, start, var_end - start));
}

static char	*replace_var(char *result, int start, int end, char *value)
{
	char	*before;
	char	*after;
	char	*temp;
	char	*new_result;

	before = ft_substr(result, 0, start);
	after = ft_strdup(result + end);
	temp = str_join(before, value);
	new_result = str_join(temp, after);
	free(before);
	free(after);
	free(temp);
	free(result);
	return (new_result);
}

static char	*process_found_var(char *result, t_var_info *var, int *i)
{
	result = replace_var(result, var->start, var->end, var->value);
	*i = var->start + ft_strlen(var->value) - 1;
	return (result);
}

static char	*process_variable(char *result, int *i, char **variable)
{
	t_var_info	var;
	int			var_index;

	var.start = *i;
	(*i)++;
	var.name = extract_var_name(result, *i, &var.end);
	if (!var.name)
		return (result);
	var_index = get_variable_index(variable, var.name);
	if (var_index != -1)
	{
		var.value = ft_strchr(variable[var_index], '=');
		if (var.value)
		{
			var.value++;
			result = process_found_var(result, &var, i);
		}
	}
	else
	{
		result = replace_var(result, var.start, var.end, "");
		*i = var.start - 1;
	}
	free(var.name);
	return (result);
}

char	*handle_dollar(char *str, char **variable)
{
	char	*result;
	int		i;

	if (!ft_strchr(str, '$'))
		return (str);
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
	{
		if (valid_to_expand(result, i))
			result = process_variable(result, &i, variable);
		i++;
	}
	return (result);
}
