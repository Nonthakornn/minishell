#include "libft.h"

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

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

int	ft_find_index(char *str, char c)
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

char	*ft_cat_str(char *s1, char *s2)
{
	int		len;
	char	*new_str;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = malloc(sizeof(char) * len);
	new_str[len] = '\0';
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		new_str[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		new_str[j] = s2[i];
		i++;
		j++;
	}
	return (new_str);
}
