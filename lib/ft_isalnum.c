#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}

int	ft_isalnum2(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_isnum(int c)
{
	return ((c >= '0' && c <= '9')
		|| (c == '-') || (c == '+'));
}

int	ft_isnum2(char *str)
{
	int	i;
	int	digit_count;

	i = 0;
	digit_count = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			i++;
			digit_count++;
		}
		else
			return (0);
	}
	if (digit_count > 19)
		return (0);
	return (1);
}
