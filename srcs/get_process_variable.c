#include "minishell.h"

char	**get_parent_variable(char *env[])
{
	char	**variable;
	int		shlvl_idx;
	int		shlvl_value;
	char	*new_shlvl;

	variable = inherited_variable(env);
	if (!variable)
		return (NULL);
	shlvl_idx = get_variable_index(variable, "SHLVL");
	if (shlvl_idx == -1)
	{
		variable = add_str_arr(variable, \
		slice("SHLVL=1", 0, ft_strlen("SHLVL=1")));
	}
	else
	{
		shlvl_value = ft_atoi(variable[shlvl_idx] + 6) + 1;
		if (shlvl_value < 0)
			shlvl_value = 0;
		new_shlvl = itoa(shlvl_value);
		edit_str_arr(variable, shlvl_idx, str_join("SHLVL=", new_shlvl));
		free(new_shlvl);
	}
	return (variable);
}

char	**get_child_variable(char **parent_variable)
{
	char	**variable;
	int		shlvl_idx;
	int		shlvl_value;
	char	*new_shlvl;

	variable = inherited_variable(parent_variable);
	if (!variable)
		return (parent_variable);
	free_str_arr(parent_variable);
	shlvl_idx = get_variable_index(variable, "SHLVL");
	if (shlvl_idx == -1)
	{
		variable = add_str_arr(variable, \
		slice("SHLVL=0", 0, ft_strlen("SHLVL=0")));
	}
	else
	{
		shlvl_value = ft_atoi(variable[shlvl_idx] + 6) - 1;
		if (shlvl_value < 0)
			shlvl_value = 0;
		new_shlvl = itoa(shlvl_value);
		edit_str_arr(variable, shlvl_idx, str_join("SHLVL=", new_shlvl));
		free(new_shlvl);
	}
	return (variable);
}
