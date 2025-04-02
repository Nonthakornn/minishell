#include "minishell.h"

bool	handle_overflow(long long result, int sign, int *status)
{
	if ((sign == 1 && result > LLONG_MAX)
		|| (sign == -1 && result * sign < LLONG_MIN))
	{
		*status = 0;
		return (true);
	}
	return (false);
}

int	count_arg(t_process	*proc)
{
	t_process	*temp;
	int			i;

	temp = proc;
	i = 0;
	while (temp->cmd[i])
		i++;
	return (i);
}

int	get_exit_code(char **var)
{
	char	*value;
	int		idx;
	int		code;

	idx = get_variable_index(var, "?=");
	if (idx < 0)
		return (0);
	value = var[idx];
	code = ft_atoi(value + 3);
	return (code);
}

void	set_exit_code(char ***var, int exit_code)
{
	int		idx;
	char	*exit_str;

	idx = get_variable_index(*var, "?");
	exit_str = itoa(exit_code);
	if (idx >= 0)
		edit_str_arr(*var, idx, str_join("$?=", exit_str));
	else
		*var = add_str_arr(*var, exit_str);
	free(exit_str);
}

void	recover_stdfd(int stdfd[2])
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(stdfd[0], STDIN_FILENO);
	dup2(stdfd[1], STDOUT_FILENO);
	close(stdfd[0]);
	close(stdfd[1]);
}
