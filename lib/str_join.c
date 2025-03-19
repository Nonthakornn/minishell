#include "libft.h"

char	*str_join(char *s1, char *s2)
{
	int		len;
	char	*new_str;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = malloc(sizeof(char) * (len + 1));
	init_str(new_str, len);
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
