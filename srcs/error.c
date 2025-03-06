#include "minishell.h"

static void	put_strerror(char *name, char *strerr)
{
	char	*str;
	char	*cur;
	int		len;

	len = ft_strlen("bash: ") + ft_strlen(name) + ft_strlen(": ") \
		+ ft_strlen(strerr);
	str = malloc(sizeof(char) * (len + 2));
	cur = str;
	ft_strcpy(cur, "bash: ");
	cur += ft_strlen("bash: ");
	ft_strcpy(cur, name);
	cur += ft_strlen(name);
	ft_strcpy(cur, ": ");
	cur += ft_strlen(": ");
	ft_strcpy(cur, strerr);
	str[len] = '\n';
	str[len + 1] = '\0';
	ft_puterror(str);
	free(str);
}

int	display_error_access(char *access_name)
{
	put_strerror(access_name, strerror(errno));
	return (1);
}

int	display_error_no_command(char *command)
{
	put_strerror(command, ": command not found\n");
	return (1);
}

int	display_error_path(char *command)
{
	if (ft_strlen(command) == 1 && command[0] == '/')
		put_strerror(command, ": Is a directory\n");
	else
		put_strerror(command, ": No such file or directory\n");
	return (1);
}
