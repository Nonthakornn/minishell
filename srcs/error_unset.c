#include "minishell.h"

int	error_unset_option(char *name)
{
	char	*start_str;
	char	*full_str;

	start_str = str_join("bash: unset: ", name);
	full_str = str_join(start_str, ": not allow options\n");
	free(start_str);
	puterror(full_str);
	free(full_str);
	return (2);
}
