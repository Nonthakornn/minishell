#include "minishell.h"

int	*get_hdin()
{
	static int in_fd;
	return (&in_fd);
}

void	set_hdin(int fd)
{
	int	*in_fd;

	in_fd = get_hdin();
	*in_fd = fd;
}

int	*get_hdout()
{
	static int out_fd;
	return (&out_fd);
}

void	set_hdout(int fd)
{
	int	*out_fd;

	out_fd = get_hdout();
	*out_fd = fd;
}