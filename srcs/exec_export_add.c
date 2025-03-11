#include "minishell.h"

static void	add_key_value(char ***variable, char *key, char *value)
{
	int		target_index;
	char	*temp;

	target_index = get_variable_index(*variable, key);
	temp = str_join(key, value);
	if (target_index < 0)
	{
		(*variable) = add_str_arr(*variable, temp);
	}
	else
	{
		if ((*variable)[target_index][0] == '$')
		{
			(*variable) = remove_str_arr(*variable, target_index);
			(*variable) = add_str_arr(*variable, temp);
		}
		else
		{
			edit_str_arr(*variable, target_index, temp);
		}
	}
}

static void	add_only_key(char ***variable, char *key)
{
	int		target_index;
	char	*temp;

	target_index = get_variable_index(*variable, key);
	if (target_index < 0)
		(*variable) = add_str_arr(*variable, slice(key, 0, ft_strlen(key)));
	else
	{
		if ((*variable)[target_index][0] == '$')
		{
			temp = slice((*variable)[target_index], 1, ft_strlen((*variable)[target_index]));
			(*variable) = remove_str_arr(*variable, target_index);
			(*variable) = add_str_arr(*variable, temp);
		}
	}
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
	if (!value)
		add_only_key(variable, key);
	else
		add_key_value(variable, key, value);
	free(key);
	free(value);
	return (0);
}

