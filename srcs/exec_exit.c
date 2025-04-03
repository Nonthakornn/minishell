#include "minishell.h"

static int	ft_atoi_exit(const char *str, int *status)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (handle_overflow(result, sign, status))
			return (0);
	}
	*status = 1;
	return ((int)((result * sign) % 256));
}

static void	not_number_exit(t_process *proc, char **var, int std[2])
{
	print_no_nl(2, "bash: exit: ");
	print_no_nl(2, proc->cmd[1]);
	print_str(2, ": numeric argument required");
	free_everything(proc, var, std);
	rl_clear_history();
	exit(2);
}

static int	too_many_args_return(void)
{
	print_no_nl(2, "bash: exit: ");
	print_str(2, "too many arguments");
	return (1);
}

static void	one_arg_exit(t_process *proc, char **var, int std[2])
{
	free_everything(proc, var, std);
	rl_clear_history();
	exit(g_signal);
}

int	exec_exit(t_process *proc, char **var, int std[2])
{
	int	args_count;
	int	valid;
	int	exit_code;

	exit_code = 0;
	args_count = count_arg(proc);
	print_str(1, "exit");
	if (args_count == 1)
		one_arg_exit(proc, var, std);
	if (args_count >= 2)
	{
		if (!ft_isnum2(proc->cmd[1]))
			not_number_exit(proc, var, std);
		exit_code = ft_atoi_exit(proc->cmd[1], &valid);
		if (!valid)
			not_number_exit(proc, var, std);
		if (args_count > 2)
			return (too_many_args_return());
		free_everything(proc, var, std);
		exit(exit_code);
	}
	return (exit_code);
}
