#include "libft.h"

int	find_startwith_index(char **str_arr, char *word)
{
	int	i;
	i = 0;
	while (str_arr && str_arr[i])
	{
		if (ft_startwith(str_arr[i], word) == 1)
			return (i);
		i++;
	}
	return (-1);
}

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
	set_zero_str_array(new_arr, old_arr_len);
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

char	**push_str_arr(char **str_arr, char *new_str)
{
	char	**new_arr;
	int		old_arr_len;
	int		i;

	old_arr_len = count_str_array(str_arr);
	new_arr = malloc(sizeof(char *) * (old_arr_len + 2));
	set_zero_str_array(new_arr, old_arr_len + 2);
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

void	edit_str_arr(char **str_arr, char *key, char *new_str)
{
	int	target_idx;

	(void)new_str;

	target_idx = find_startwith_index(str_arr, key);
	if (target_idx < 0)
		return ;
	free(str_arr[target_idx]);
	str_arr[target_idx] = ft_cat_str(key, new_str);
}
