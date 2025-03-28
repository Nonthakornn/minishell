#include "minishell.h"

static char	*getopwd_str(char ***var)
{
	int		pwd_idx;
	char	*pwd_str;
	int		eq_idx;
	char	*path;
	char	*opwd;

	pwd_idx = get_variable_index(*var, "PWD");
	if (pwd_idx < 0)
		return (slice("OLDPWD", 0, 6));
	pwd_str = (*var)[pwd_idx];
	eq_idx = find_index(pwd_str, '=');
	if (eq_idx == -1)
		return (slice("OLDPWD", 0, 6));
	path = slice(pwd_str, eq_idx + 1, ft_strlen(pwd_str));
	opwd = str_join("OLDPWD=", path);
	free(path);
	return (opwd);
}

static void	update_opwd(char ***var)
{
	char	*str;
	int		idx;

	str = getopwd_str(var);
	idx = get_variable_index(*var, "OLDPWD");
	if (idx < 0)
		(*var) = add_str_arr(*var, str_join("$", str));
	else
	{
		if ((*var)[idx][0] == '$')
			edit_str_arr(*var, idx, str_join("$", str));
		else
			edit_str_arr(*var, idx, slice(str, 0, ft_strlen(str)));
	}
	free(str);
}

static void	update_pwd(char ***var)
{
	int	target_index;

	target_index = get_variable_index(*var, "PWD");
	if (target_index < 0)
		(*var) = add_str_arr(*var, getcwd_variable("$PWD="));
	else
	{
		if ((*var)[target_index][0] == '$')
			edit_str_arr(*var, target_index, getcwd_variable("$PWD="));
		else
			edit_str_arr(*var, target_index, getcwd_variable("PWD="));
	}
	target_index = get_variable_index(*var, "@PWD");
	if (target_index == -1)
		(*var) = add_str_arr(*var, getcwd_variable("@PWD="));
	else
		edit_str_arr(*var, target_index, getcwd_variable("@PWD="));
}

int	exec_cd(t_process *process, char ***var)
{
	int	exit_code;

	exit_code = exec_chdir(process, *var);
	if (exit_code != 0)
		return (exit_code);
	update_opwd(var);
	update_pwd(var);
	return (exit_code);
}

int	is_dir(char *path)
{
	DIR	*d;

	d = opendir(path);
	if (!d)
		return (0);
	closedir(d);
	return (1);
}
