#include "minishell.h"

int	key_exist(char *var_str, char *key)
{
	if (ft_strlen(key) == 0 || ft_strlen(var_str) == 0)
		return (0);
	if (ft_strlen(key) > ft_strlen(var_str))
		return (0);
	if (var_str[0] == '$')
		var_str++;
	if (ft_strcmp(var_str, key, '=') == 0)
		return (1);
	return (0);
}

int	get_variable_index(char **variable, char *key)
{
	int	i;

	i = 0;
	while (variable && variable[i])
	{
		if (key_exist(variable[i], key))
			return (i);
		i++;
	}
	return (-1);
}

int	count_variable(char *env[])
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (env && env[i])
	{
		if (find_index(env[i], '=') != -1)
			c++;
		i++;
	}
	return (c);
}

void	print_variable(char **variable)
{
	int	i;

	i = 0;
	while (variable && variable[i])
	{
		if (find_index(variable[i], '=') != -1)
			print_str(1, variable[i]);
		i++;
	}
}

char	**inherited_variable(char *env[])
{
	int		var_len;
	char	**str_arr;
	int		i;

	var_len = count_variable(env);
	if (var_len == 0)
		return (NULL);
	str_arr = malloc(sizeof(char *) * (var_len + 1));
	init_str_array(str_arr, var_len);
	i = 0;
	while (env[i])
	{
		if (find_index(env[i], '=') == -1)
			continue ;
		str_arr[i] = slice(env[i], 0, ft_strlen(env[i]));
		if (!str_arr[i])
			return (free_str_arr(str_arr), NULL);
		i++;
	}
	return (str_arr);
}
