#include "minishell.h"

char	**load_env(char *env[])
{
	char	**shell_env;

	shell_env = new_str_arr(env);
	if (!shell_env)
		return (NULL);
	return (NULL);
}
