#include "minishell.h"

static char	*ft_join_dir(char *dir, char *cmd)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!dir | !cmd)
		return (NULL);
	new_str = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
	if (!new_str)
		return (NULL);
	new_str[ft_strlen(dir) + ft_strlen(cmd) + 1] = '\0';
	i = 0;
	while (i < ft_strlen(dir))
	{
		new_str[i] = dir[i];
		i++;
	}
	new_str[i] = '/';
	i++;
	j = 0;
	while (j < ft_strlen(cmd))
	{
		new_str[i + j] = cmd[j];
		j++;
	}
	return (new_str);
}

static char	*ft_check_path_command(char *command)
{
	if (ft_strlen(command) == 1)
	{
		ft_puterror("bash: /: Is a directory\n");
		return (NULL);
	}
	if (access(command, F_OK) == 0)
		return (ft_slice(command, 0, ft_strlen(command)));
	display_error_access(command);
	return (NULL);
}

static char	*ft_find_accessible_path(char *path_str, char *command)
{
	char	**split_path;
	char	*env_path;
	char	*cmd_path;
	int		i;

	if (ft_strlen(path_str) <= 5)
	{
		display_error_path(command);
		return (display_error_path(command), NULL);
	}
	env_path = ft_slice(path_str, 5, ft_strlen(path_str));
	if (!env_path)
		return (NULL);
	split_path = ft_str_split(env_path, " :");
	free(env_path);
	i = 0;
	while (split_path && split_path[i])
	{
		cmd_path = ft_join_dir(split_path[i], command);
		if (cmd_path && access(cmd_path, F_OK) == 0)
			return (clear_substr(split_path), cmd_path);
		free(cmd_path);
		i++;
	}
	return (clear_substr(split_path), NULL);
}

static int	ft_get_path_index(char *env[])
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_startwith(env[i], "PATH=") == 1)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_get_path(char *env[], char *command)
{
	int		path_index;
	char	*accessible_path;

	if (ft_find_index(command, '/') != -1)
		return (ft_check_path_command(command));
	path_index = ft_get_path_index(env);
	if (path_index == -1)
	{
		display_error_path(command);
		return (NULL);
	}
	accessible_path = ft_find_accessible_path(env[path_index], command);
	if (!accessible_path)
	{
		display_error_no_command(command);
		return (NULL);
	}
	return (accessible_path);
}