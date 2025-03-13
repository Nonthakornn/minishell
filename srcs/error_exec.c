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
}

int	error_access(char *access_name)
{
	put_strerror(access_name, strerror(errno));
	return (1);
}

int	error_no_command(char *command)
{
	put_strerror(command, "command not found\n");
	return (1);
}

int	error_path(char *command)
{
	if (ft_strlen(command) == 1 && command[0] == '/')
		put_strerror(command, "Is a directory\n");
	else
		put_strerror(command, "No such file or directory\n");
	return (1);
}
