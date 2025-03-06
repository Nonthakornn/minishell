#include "libft.h"

bool is_space(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}


void	ft_puterror(char *str)
{
	write(2, str, ft_strlen(str));
}

int	ft_startwith(char *str, char *word)
{
	size_t	i;

	if (!str || !word || ft_strlen(str) < ft_strlen(word))
		return (-1);
	i = 0;
	while (i < ft_strlen(word))
	{
		if (str[i] != word[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_slice(char *src, size_t start, size_t end)
{
	char	*rs;
	size_t	i;

	if (end > ft_strlen(src))
		end = ft_strlen(src);
	if (!src || start >= end)
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

static size_t	ft_split_number(char *str, char *sep)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	while (str && str[i])
	{
		if (str[i] && ft_find_index(sep, str[i]) == -1 && \
		(ft_find_index(sep, str[i + 1]) >= 0 || !str[i + 1]))
			c++;
		i++;
	}
	return (c);
}

char	**ft_str_split(char *str, char *sep)
{
	size_t	n;
	size_t	i;
	size_t	j;
	size_t	k;
	char	**split;

	n = ft_split_number(str, sep);
	if (n == 0)
		return (NULL);
	i = 0;
	k = 0;
	split = malloc(sizeof(char *) * (n + 1));
	while (str[i])
	{
		while (str[i] && ft_find_index(sep, str[i]) >= 0)
			i++;
		j = 0;
		while (str[i + j] && ft_find_index(sep, str[i + j]) == -1)
			j++;
		split[k++] = ft_slice(str, i, i + j);
		i += j;
	}
	split[n] = NULL;
	return (split);
}

void	clear_substr(char **substr)
{
	size_t	i;

	i = 0;
	while (substr && substr[i])
	{
		free(substr[i]);
		i++;
	}
	free(substr);
}
