#include "minishell.h"

int	*get_stdin()
{
	static int	stdin_fd = 0;
	return (&stdin_fd);
}

void	set_stdin(int stdin_fd)
{
	int	*in;

	in = get_stdin();
	*in = stdin_fd;
}

int	*get_stdout()
{
	static int	stdout_fd = 1;
	return (&stdout_fd);
}

void	set_stdout(int stdout_fd)
{
	int	*out;

	out = get_stdout();
	*out = stdout_fd;
}

