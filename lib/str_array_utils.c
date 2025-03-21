#include "libft.h"

char	**new_str_arr(int len)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * len);
	i = 0;
	while (i < len)
	{
		arr[i] = NULL;
		i++;
	}
	return (arr);
}

int	count_str_arr(char *arr[])
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

void	print_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr && str_arr[i])
	{
		print_str(1, str_arr[i]);
		i++;
	}
}
