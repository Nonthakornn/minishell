#include "libft.h"

void	init_str(char *str, int len)
{
	int	i;

	i = 0;
	while (i <= len)
	{
		str[i] = '\0';
		i++;
	}
}

void	ft_strcpy(char *dst, char *src)
{
	int	i;

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

size_t	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	find_index(char *str, char c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
