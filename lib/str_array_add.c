#include "libft.h"

char	**add_str_arr(char **str_arr, char *new_str)
{
	char	**new_arr;
	int		old_arr_len;
	int		i;

	old_arr_len = count_str_arr(str_arr);
	new_arr = new_str_arr(old_arr_len + 2);
	i = 0;
	while (str_arr && str_arr[i])
	{
		new_arr[i] = str_arr[i];
		i++;
	}
	free(str_arr);
	new_arr[i] = new_str;
	return (new_arr);
}
