#include "minishell.h"

char	*getcwd_variable(char *key)
{
	char	*buff;
	char	*var;

	buff = new_str(1024);
	getcwd(buff, 1023);
	var = str_join(key, buff);
	free(buff);
	return (var);
}

static void	print_pwd(char **var)
{
	char	buff[1024];
	int		i;

	i = 0;
	while (var && var[i])
	{
		if (startwith(var[i], "@PWD="))
		{
			print_str(1, var[i] + 5);
			return ;
		}
		i++;
	}
	getcwd(buff, 1024);
	print_str(1, buff);
}

int	exec_pwd(t_process *process, char ***var)
{
	int	i;

	i = 1;
	while (process->cmd[i])
	{
		if (process->cmd[i][0] == '-')
		{
			error_pwd_option(process->cmd[i]);
			return (2);
		}
		i++;
	}
	print_pwd(*var);
	return (0);
}
