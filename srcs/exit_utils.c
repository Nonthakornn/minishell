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
