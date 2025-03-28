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

int get_exit_code(char **var)
{
	char	*value;
	int		idx;
	int		code;

	idx = get_variable_index(var, "?=");
	// print_str_arr(var);
	// printf("%d\n", idx);
	if (idx < 0)
		return (0);
	value = var[idx];
	code = ft_atoi(value + 3);
	return (code);
}
