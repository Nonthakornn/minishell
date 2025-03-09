#include "libft.h"

int	ft_atoi(char *nstr)
{
	int	sign;
	int	number;
	int	i;

	sign = 1;
	number = 0;
	i = 0;
	if (!nstr)
		return (0);
	while (nstr[i] == 32 || nstr[i] == 9)
		i++;
	if (nstr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (nstr[i] >= '0' && nstr[i] <= '9')
	{
		number = (number * 10) - (nstr[i] - '0');
		i++;
	}
	return (-1 * number * sign);
}
