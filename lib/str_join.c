#include "libft.h"

char	*str_join(char *s1, char *s2)
{
	int		len;
	char	*str;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = new_str(len + 1);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	return (str);
}
