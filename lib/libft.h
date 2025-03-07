#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

int		ft_startwith(char *str, char *word);
int		ft_find_index(char *str, char c);
char	*ft_slice(char *src, size_t start, size_t end);
char	**ft_str_split(char *str, char *sep);
bool	is_space(int c);
void	ft_print_str(int fd, char *str);
void	ft_strcpy(char *dst, char *src);
void	ft_puterror(char *str);
void	clear_substr(char **substr);
size_t	ft_strlen(char *str);
int		count_str_array(char *arr[]);
void	set_zero_str_array(char *arr[], int arr_len);
char	**new_str_arr(char *arr[]);
void	free_str_arr(char **arr);
char	**remove_str_arr(char **str_arr, int removed_index);
void	print_str_array(char **str_arr);
int		find_startwith_index(char **str_arr, char *word);
char	**push_str_arr(char **str_arr, char *new_str);
char	*ft_cat_str(char *s1, char *s2);
void	edit_str_arr(char **str_arr, char *key, char *new_str);

#endif
