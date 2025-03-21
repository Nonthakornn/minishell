#include "minishell.h"

static void	add_key_value(char ***variable, char *key, char *value)
{
	int		target_index;
	char	*temp;

	target_index = get_variable_index(*variable, key);
	temp = str_join(key, value);
	if (target_index < 0)
		(*variable) = add_str_arr(*variable, temp);
	else
	{
		if ((*variable)[target_index][0] == '$')
		{
			(*variable) = rm_str_arr(*variable, target_index);
			(*variable) = add_str_arr(*variable, temp);
		}
		else
			edit_str_arr(*variable, target_index, temp);
	}
	free(key);
	free(value);
}

static void	add_only_key(char ***variable, char *key)
{
	int		target_index;
	char	*target_str;
	char	*temp;

	target_index = get_variable_index(*variable, key);
	if (target_index < 0)
		(*variable) = add_str_arr(*variable, slice(key, 0, ft_strlen(key)));
	else
	{
		target_str = (*variable)[target_index];
		if (target_str[0] == '$')
		{
			temp = slice(target_str, 1, ft_strlen(target_str));
			(*variable) = rm_str_arr(*variable, target_index);
			(*variable) = add_str_arr(*variable, temp);
		}
	}
	free(key);
}

static int	valid_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || \
	c == '_' || \
	(c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

static int	is_valid_key(char *key)
{
	int	i;

	if (!key)
		return (0);
	if (!valid_char(key[0]))
		return (0);
	i = 1;
	while (key[i] && key[i] != '=')
	{
		if (!valid_char(key[i]) && \
		!(key[i] >= '0' && key[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	add_export(char ***variable, char *str)
{
	int		eq_index;
	char	*key;
	char	*value;

	eq_index = find_index(str, '=');
	key = NULL;
	value = NULL;
	if (eq_index >= 0)
	{
		key = slice(str, 0, eq_index + 1);
		value = slice(str, eq_index + 1, ft_strlen(str));
	}
	else
		key = slice(str, 0, ft_strlen(str));
	if (key && key[0] == '-')
		return (error_export_option(key, value));
	else if (!is_valid_key(key))
		return (error_export_name(key, value));
	else if (!value)
		add_only_key(variable, key);
	else
		add_key_value(variable, key, value);
	return (0);
}
