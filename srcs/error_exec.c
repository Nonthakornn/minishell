#include "minishell.h"

void	put_strerror(char *name, char *strerr)
{
	char	*start_str;
	char	*cmd_str;
	char	*full_str;

	start_str = str_join("bash: ", name);
	cmd_str = str_join(start_str, ": ");
	free(start_str);
	full_str = str_join(cmd_str, strerr);
	free(cmd_str);
	puterror(full_str);
	free(full_str);
	write(2, "\n", 1);
}

int	error_access(char *access_name)
{
	put_strerror(access_name, strerror(errno));
	return (1);
}

int	error_no_command(char *command)
{
	char	*cmd_str;

	cmd_str = str_join(command, ": command not found\n");
	puterror(cmd_str);
	free(cmd_str);
	return (1);
}

int	error_no_path(char *command)
{
	put_strerror(command, "No such file or directory");
	return (1);
}

int	error_argument(char *cmd, char *arg)
{
	char	*init_str;
	char	*cmd_str;

	init_str = str_join(cmd, ": ");
	cmd_str = str_join(init_str, arg);
	free(init_str);
	put_strerror(cmd_str , strerror(errno));
	free(cmd_str);
	return (1);
}
