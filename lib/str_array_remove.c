#include "libft.h"

char	**remove_str_arr(char **str_arr, int removed_index)
{
	char	**new_arr;
	int		old_arr_len;
	int		i;
	int		j;

	old_arr_len = count_str_array(str_arr);
	if (old_arr_len == 0 || removed_index < 0 || removed_index >= old_arr_len)
		return (str_arr);
	new_arr = malloc(sizeof(char *) * old_arr_len);
	init_str_array(new_arr, old_arr_len - 1);
	i = 0;
	j = 0;
	while (str_arr[i])
	{
		if (i == removed_index)
			free(str_arr[i]);
		else
		{
			new_arr[j] = str_arr[i];
			j++;
		}
		i++;
	}
	free(str_arr);
	return (new_arr);
}
