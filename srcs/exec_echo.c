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

static void	process_flag_n(char **cmd, int start_index)
{
	int	i;
	int	first_word;

	i = start_index;
	first_word = 1;
	while (cmd[i])
	{
		if (!first_word)
			printf(" ");
		else
			first_word = 0;
		printf("%s", cmd[i]);
		i++;
	}
}

int	exec_echo(t_process *process, char **variable)
{
	int		i;
	int		first_word;
	char	**cmd;

	(void)variable;
	i = 1;
	first_word = 1;
	cmd = process->cmd;
	if (cmd[1] && check_n(cmd[1]))
	{
		process_flag_n(cmd, 2);
		return (0);
	}
	while (cmd[i])
	{
		if (!first_word)
			printf(" ");
		else
			first_word = 0;
		printf("%s", cmd[i]);
		i++;
	}
	printf("\n");
	return (0);
}
