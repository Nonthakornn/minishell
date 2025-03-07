#include "minishell.h"

char	**load_variable(char *env[])
{
	char	**variable;

	variable = new_str_arr(env);
	if (!variable)
		return (NULL);
	edit_str_arr(variable, "SHLVL=", "14");
	return (variable);
}
