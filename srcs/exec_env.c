#include "minishell.h"

static void	print_variable(char **var)
{
	int	i;

	i = 0;
	while (var && var[i])
	{
		if (startwith(var[i], "_="))
		{
			print_str(1, "_=/usr/bin/env");
			i++;
			continue ;
		}
		if (is_include(var[i], '=') && \
		!startwith(var[i], "$") && !startwith(var[i], "@"))
			print_str(1, var[i]);
		i++;
	}
}

int	exec_env(t_process *process, char **var)
{
	int	cmd_count;

	cmd_count = count_str_arr(process->cmd);
	if (cmd_count != 1)
	{
		put_strerror("env", "too many arguments");
		return (1);
	}
	print_variable(var);
	return (0);
}
