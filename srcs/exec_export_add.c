#include "minishell.h"

static void	add_key_value(char ***var, char *key, char *value)
{
	int		target_index;
	char	*temp;

	print_str_arr(*var);
	target_index = get_variable_index(*var, key);
	printf("%d\n", target_index);
	temp = str_join(key, value);
	if (target_index < 0)
		(*var) = add_str_arr(*var, temp);
	else
	{
		if ((*var)[target_index][0] == '$')
		{
			(*var) = rm_str_arr(*var, target_index);
			(*var) = add_str_arr(*var, temp);
		}
		else
			edit_str_arr(*var, target_index, temp);
	}
	free(key);
	free(value);
}

static void	add_only_key(char ***var, char *key)
{
	int		target_index;
	char	*target_str;
	char	*temp;

	target_index = get_variable_index(*var, key);
	if (target_index < 0)
		(*var) = add_str_arr(*var, slice(key, 0, ft_strlen(key)));
	else
	{
		target_str = (*var)[target_index];
		if (target_str[0] == '$')
		{
			temp = slice(target_str, 1, ft_strlen(target_str));
			(*var) = rm_str_arr(*var, target_index);
			(*var) = add_str_arr(*var, temp);
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

int	add_export(char ***var, char *str)
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
		add_only_key(var, key);
	else
		add_key_value(var, key, value);
	return (0);
}
