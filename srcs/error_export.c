#include "minishell.h"

int	error_export_name(char *key, char *value)
{
	char	*start_str;
	char	*full_str;

	start_str = str_join("bash: export: `", key);
	full_str = str_join(start_str, "': not a valid identifier\n");
	free(start_str);
	puterror(full_str);
	free(full_str);
	free(key);
	free(value);
	return (1);
}
