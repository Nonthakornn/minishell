#include "libft.h"

char	**malloc_array(int cmd_count)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * (cmd_count + 1));
	if (!cmd)
		return (NULL);
	return (cmd);
}
