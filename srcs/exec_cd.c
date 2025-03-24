#include "minishell.h"

static char	*getopwd_str(char ***variable)
{
	int		pwd_idx;
	char	*pwd_str;
	int		eq_idx;
	char	*path;
	char	*opwd;

	pwd_idx = get_variable_index(*variable, "PWD");
	if (pwd_idx < 0)
		return (slice("OLDPWD", 0, 6));
	pwd_str = (*variable)[pwd_idx];
	eq_idx = find_index(pwd_str, '=');
	if (eq_idx == -1)
		return (slice("OLDPWD", 0, 6));
	path = slice(pwd_str, eq_idx + 1, ft_strlen(pwd_str));
	opwd = str_join("OLDPWD=", path);
	free(path);
	return (opwd);
}

static void	update_opwd(char ***variable)
{
	char	*str;
	int		idx;

	str = getopwd_str(variable);
	idx = get_variable_index(*variable, "OLDPWD");
	if (idx < 0)
		(*variable) = add_str_arr(*variable, str_join("$", str));
	else
	{
		if ((*variable)[idx][0] == '$')
			edit_str_arr(*variable, idx, str_join("$", str));
		else
			edit_str_arr(*variable, idx, slice(str, 0, ft_strlen(str)));
	}
	free(str);
}

static void	update_pwd(char ***variable)
{
	int	target_index;

	target_index = get_variable_index(*variable, "PWD");
	if (target_index < 0)
		(*variable) = add_str_arr(*variable, getcwd_variable("$PWD="));
	else
	{
		if ((*variable)[target_index][0] == '$')
			edit_str_arr(*variable, target_index, getcwd_variable("$PWD="));
		else
			edit_str_arr(*variable, target_index, getcwd_variable("PWD="));
	}
	target_index = get_variable_index(*variable, "@PWD");
	if (target_index == -1)
		(*variable) = add_str_arr(*variable, getcwd_variable("@PWD="));
	else
		edit_str_arr(*variable, target_index, getcwd_variable("@PWD="));
}

int	exec_cd(t_process *process, char ***variable)
{
	int	exit_code;

	exit_code = exec_chdir(process, *variable);
	if (exit_code != 0)
		return (exit_code);
	update_opwd(variable);
	update_pwd(variable);
	return (exit_code);
}
