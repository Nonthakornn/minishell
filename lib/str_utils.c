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

int	ft_strcmp(char *s1, char *s2, char terminal)
{
	int		i;
	char	last_s1;
	char	last_s2;

	if (!s1 && !s2)
		return (0);
	if (!s1 && s2)
		return (-1);
	if (s1 && !s2)
		return (1);
	i = 0;
	while (s1[i] && s1[i] != terminal \
	&& s2[i] && s2[i] != terminal && s1[i] == s2[i])
		i++;
	last_s1 = s1[i];
	last_s2 = s2[i];
	if (last_s1 == terminal)
		last_s1 = '\0';
	if (last_s2 == terminal)
		last_s2 = '\0';
	return (last_s1 - last_s2);
}
