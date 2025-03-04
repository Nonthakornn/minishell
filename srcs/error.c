#include "minishell.h"

int	display_error_access(char *access_name)
{
	ft_puterror("bash: ");
	ft_puterror(access_name);
	ft_puterror(": ");
	ft_puterror(strerror(errno));
	ft_puterror("\n");
	return (1);
}

int	display_error_no_command(char *command)
{
	ft_puterror(command);
	ft_puterror(": command not found\n");
	return (1);
}

int	display_error_path(char *command)
{
	ft_puterror("bash: ");
	ft_puterror(command);
	if (ft_strlen(command) == 1 && command[0] == '/')
		ft_puterror(": Is a directory\n");
	else
		ft_puterror(": No such file or directory\n");
	return (1);
}