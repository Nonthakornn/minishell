#include "minishell.h"

static int	chdir_to_home_env(char **var)
{
	int	home_index;

	home_index = get_variable_index(var, "HOME=");
	if (home_index == -1)
		return (put_strerror("cd", " HOME not set"), 1);
	if (chdir(var[home_index] + 5) < 0)
	{
		put_strerror(var[home_index] + 5, strerror(errno));
		return (1);
	}
	return (chdir(var[home_index] + 5), 1);
}

static char	*get_home_path(char *pwd_path)
{
	int	end;

	if (!startwith(pwd_path, "@PWD=/home/"))
		return (slice("/home/", 0, 6));
	end = 11;
	while (pwd_path[end] && pwd_path[end] != '/')
		end++;
	return (slice(pwd_path, 5, end));
}

static int	chdir_to_home(char **var)
{
	int		pwd_index;
	char	*home_path;

	pwd_index = get_variable_index(var, "@PWD");
	if (pwd_index == -1)
		return (put_strerror("cd", " HOME not set"), 1);
	home_path = get_home_path(var[pwd_index]);
	if (chdir(home_path) < 0)
	{
		put_strerror(home_path, strerror(errno));
		free(home_path);
		return (1);
	}
	free(home_path);
	return (0);
}

static int	chdir_to_oldpwd(char **var)
{
	int	opwd_index;

	opwd_index = get_variable_index(var, "OLDPWD=");
	if (opwd_index == -1)
		return (put_strerror("cd", " OLDPWD not set"), 1);
	if (chdir(var[opwd_index] + 7) < 0)
	{
		put_strerror(var[opwd_index] + 7, strerror(errno));
		return (1);
	}
	return (0);
}

int	exec_chdir(t_process *process, char **var)
{
	int		cmd_number;
	char	*arg;

	cmd_number = count_str_arr(process->cmd);
	if (cmd_number > 2)
		return (put_strerror("cd", "too many arguments"), 1);
	if (cmd_number == 1)
		return (chdir_to_home_env(var));
	arg = (process->cmd)[1];
	if (ft_strlen(arg) > 1 && arg[0] == '-')
		return (put_strerror("cd", " not allow options"), 2);
	if (is_equal(arg, "-"))
		return (chdir_to_oldpwd(var));
	if (is_equal(arg, "~"))
		return (chdir_to_home(var));
	if (chdir(arg) < 0)
		return (put_strerror(arg, strerror(errno)), 1);
	return (0);
}
