#include "minishell.h"

static int	remove_number(char **variable, char *key)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (variable && variable[i])
	{
		if (key_exist(variable[i], key))
			count++;
		i++;
	}
	return (count);
}

static char	**remove_variable(char **var, char *key)
{
	char	**new_arr;
	int		old_len;
	int		i;
	int		j;

	old_len = count_str_arr(var);
	if (old_len == 0 || remove_number(var, key) == 0)
		return (var);
	new_arr = new_str_arr(old_len - 1 + remove_number(var, key));
	i = 0;
	j = 0;
	while (var[i])
	{
		if (key_exist(var[i], key))
			free(var[i]);
		else
		{
			new_arr[j] = var[i];
			j++;
		}
		i++;
	}
	return (free(var), new_arr);
}

int	exec_unset(t_process *process, char ***variable)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	while (process->cmd[i])
	{
		if (process->cmd[i][0] == '-')
		{
			exit_code = error_unset_option(process->cmd[i]);
			break ;
		}
		if (process->cmd[i][0] == '@')
		{
			i++;
			continue ;
		}
		(*variable) = remove_variable(*variable, process->cmd[i]);
		i++;
	}
	return (exit_code);
}
