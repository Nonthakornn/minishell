#include "minishell.h"

static void	print_variable(char **variable)
{
	int	i;

	i = 0;
	while (variable && variable[i])
	{
		if (startwith(variable[i], "_="))
		{
			print_str(1, "_=/usr/bin/env");
			i++;
			continue ;
		}
		if (is_include(variable[i], '=') && \
		!startwith(variable[i], "$") && !startwith(variable[i], "@"))
			print_str(1, variable[i]);
		i++;
	}
}

int	exec_env(t_process *process, char **variable)
{
	int	cmd_count;

	cmd_count = count_str_arr(process->cmd);
	if (cmd_count != 1)
	{
		put_strerror("env", "too many arguments");
		return (1);
	}
	print_variable(variable);
	return (0);
}
