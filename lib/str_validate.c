#include "libft.h"

int	startwith(char *str, char *word)
{
	size_t	i;

	if (!str || !word || ft_strlen(str) < ft_strlen(word))
		return (0);
	i = 0;
	while (i < ft_strlen(word))
	{
		if (str[i] != word[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_equal(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

bool	is_space(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

int	is_include(char *str, char c)
{
	int	i;

	if (ft_strlen(str) < 1)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (1);
		i++;
	}
	return (0);
}
