#include "minishell.h"

int	*get_stdin(void)
{
	static int	stdin_fd;

	return (&stdin_fd);
}

void	set_stdin(int stdin_fd)
{
	int	*in;

	in = get_stdin();
	*in = stdin_fd;
}

int	*get_stdout(void)
{
	static int	stdout_fd;

	return (&stdout_fd);
}

void	set_stdout(int stdout_fd)
{
	int	*out;

	out = get_stdout();
	*out = stdout_fd;
}
