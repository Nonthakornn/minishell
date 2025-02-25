#include "minishell.h"

char	*get_str_token(t_token_type type)
{
	if (type == CMD)
		return ("CMD");
	else if (type == READ_FILE)
		return ("READ_FILE");
	else if (type == HERE_DOC)
		return ("HERE_DOC");
	else if (type == WRITE_FILE)
		return ("WRITE_FILE");
	else if (type == APPEND_FILE)
		return ("APPEND_FILE");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == ENV_VAR)
		return ("ENV_VAR");
	else
	{
		printf("Type is not defined\n");
		return (NULL);
	}
}
