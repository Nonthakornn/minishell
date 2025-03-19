#include "libft.h"

char	*slice(char *src, size_t start, size_t end)
{
	char	*rs;
	size_t	i;

	if (end > ft_strlen(src))
		end = ft_strlen(src);
	if (!src)
		return (NULL);
	i = 0;
	rs = malloc(sizeof(char) * (end - start + 1));
	if (!rs)
		return (NULL);
	while (start < end)
		rs[i++] = src[start++];
	rs[i] = '\0';
	return (rs);
}

static size_t	split_number(char *str, char *sep)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	while (str && str[i])
	{
		if (str[i] && find_index(sep, str[i]) == -1 && \
		(find_index(sep, str[i + 1]) >= 0 || !str[i + 1]))
			c++;
		i++;
	}
	return (c);
}

char	**str_split(char *str, char *sep)
{
	size_t	n;
	size_t	i;
	size_t	j;
	size_t	k;
	char	**split;

	n = split_number(str, sep);
	if (n == 0)
		return (NULL);
	i = 0;
	k = 0;
	split = malloc(sizeof(char *) * (n + 1));
	while (str[i])
	{
		while (str[i] && find_index(sep, str[i]) >= 0)
			i++;
		j = 0;
		while (str[i + j] && find_index(sep, str[i + j]) == -1)
			j++;
		split[k++] = slice(str, i, i + j);
		i += j;
	}
	split[n] = NULL;
	return (split);
}
