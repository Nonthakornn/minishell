#include "libft.h"

static int	get_number_len(int nb)
{
	size_t	number_len;

	if (nb > 0)
		nb = nb * -1;
	number_len = 1;
	while (nb < (-9))
	{
		nb /= 10;
		number_len += 1;
	}
	return (number_len);
}

static char	*get_char_molloc(int nb, size_t number_len)
{
	char	*text;

	if (nb < 0)
	{
		text = (char *)malloc((number_len + 2) * sizeof(char));
		if (!text)
			return (NULL);
		text[0] = '-';
		text[number_len + 1] = '\0';
	}
	else
	{
		text = (char *)malloc((number_len + 1) * sizeof(char));
		if (!text)
			return (NULL);
		text[number_len] = '\0';
	}
	return (text);
}

static int	get_divisor(size_t number_len)
{
	int	divisor;

	divisor = -1;
	while (number_len > 1)
	{
		divisor *= 10;
		number_len--;
	}
	return (divisor);
}

char	*itoa(int n)
{
	char			*text;
	unsigned int	i;
	size_t			number_len;
	int				divisor;

	number_len = get_number_len(n);
	text = get_char_molloc(n, number_len);
	if (!text)
		return (NULL);
	i = 1;
	if (n >= 0)
	{
		n = n * -1;
		i--;
	}
	while (number_len > 0)
	{
		divisor = get_divisor(number_len);
		text[i] = '0' + (n / divisor);
		n %= divisor;
		number_len--;
		i++;
	}
	return (text);
}
