#include "libft.h"

void	init_str_array(char *arr[], int arr_len)
{
	int	i;

	i = 0;
	while (i <= arr_len)
	{
		arr[i] = NULL;
		i++;
	}
}

int	count_str_array(char *arr[])
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void	free_str_arr(char **str_arr)
{
	int		i;

	i = 0;
	while (str_arr && str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

void	edit_str_arr(char **str_arr, int edited_index, char *new_str)
{
	if (edited_index < 0)
		return ;
	free(str_arr[edited_index]);
	str_arr[edited_index] = new_str;
}

void	print_str_array(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr && str_arr[i])
	{
		print_str(1, str_arr[i]);
		i++;
	}
}
