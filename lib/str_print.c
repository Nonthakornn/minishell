#include "libft.h"

void	print_str(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

void	puterror(char *str)
{
	write(2, str, ft_strlen(str));
}
