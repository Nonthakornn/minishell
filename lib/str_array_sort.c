#include "libft.h"

static char **copy_arr(char **str)
{
	char	**copy_arr;
	int		arr_len;
	int		i;

	arr_len = count_str_array(str);
	copy_arr = malloc(sizeof(char *) * (arr_len + 1));
	init_str_array(copy_arr, arr_len);
	i = 0;
	while (str && str[i])
	{
		copy_arr[i] = slice(str[i], 0, ft_strlen(str[i]));
		i++;
	}
	return (copy_arr);
}

static int	find_min_arr(char **str)
{
	int		i;
	int		min_index;
	char	*min_str;

	if (!str)
		return (-1);
	i = 0;
	min_str = str[0];
	min_index = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], min_str, '=') < 0)
		{
			min_str = str[i];
			min_index = i;
		}
		i++;
	}
	return (min_index);
}

char	**sort_arr(char **str_arr)
{
	char	**sort_arr;
	int		arr_len;
	int		min_index;
	int		i;
	char	**temp;

	arr_len = count_str_array(str_arr);
	sort_arr = malloc(sizeof(char *) * (arr_len + 1));
	init_str_array(sort_arr, arr_len);
	temp = copy_arr(str_arr);
	i = 0;
	while (i < arr_len)
	{
		min_index = find_min_arr(temp);
		sort_arr[i] = slice(temp[min_index], 0 , ft_strlen(temp[min_index]));
		temp = remove_str_arr(temp, min_index);
		i++;
	}
	free(temp);
	return (sort_arr);
}
