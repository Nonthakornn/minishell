#include "minishell.h"

static bool	check_n(char *cmd)
{
	int	i;

	i = 0;
	while (is_space(cmd[i]))
		i++;
	if (cmd[i] != '-')
		return (false);
	i++;
	while (cmd[i] == 'n')
		i++;
	if (!cmd[i])
		return (true);
	return (false);
}

static void	print_args(char **cmd, int start, bool add_newline)
{
	int	i;

	i = start;
	if (cmd[i])
		printf("%s", cmd[i++]);
	while (cmd[i])
		printf(" %s", cmd[i++]);
	if (add_newline)
		printf("\n");
}

int	exec_echo(t_process *process, char **variable)
{
	char	**cmd;

	(void)variable;
	cmd = process->cmd;
	if (cmd[1] && check_n(cmd[1]))
		print_args(cmd, 2, false);
	else
		print_args(cmd, 1, true);
	return (0);
}
