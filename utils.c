#include "minishell.h"

void	ft_print_str(int fd, char *str)
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

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
void ft_strcpy(char *dst, char *src)
{
	int i;

	i = 0;
	if (!src || !dst)
		return ;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

bool is_space(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}