#include "libft.h"

void	set_zero_str_array(char *arr[], int arr_len)
{
	int i;

	i = 0;
	while (i < arr_len)
	{
		arr[i] = NULL;
		i++;
	}
}

int	count_str_array(char *arr[])
{
	int	i;

	i = 0;
	while(arr && arr[i])
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

char	**new_str_arr(char *arr[])
{
	int		arr_len;
	char	**str_arr;
	int		i;

	arr_len = count_str_array(arr);
	if (arr_len == 0)
		return (NULL);
	str_arr = malloc(sizeof(char *) * (arr_len + 1));
	set_zero_str_array(str_arr, arr_len + 1);
	i = 0;
	while (arr[i])
	{
		str_arr[i] = ft_slice(arr[i], 0, ft_strlen(arr[i]));
		if (!str_arr[i])
		{
			free_str_arr(str_arr);
			return (NULL);
		}
		i++;
	}
	return (str_arr);
}

void	print_str_array(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr && str_arr[i])
	{
		ft_print_str(1, str_arr[i]);
		i++;
	}
}


