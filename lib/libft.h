#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

int		startwith(char *str, char *word);
int		find_index(char *str, char c);
int		ft_strcmp(char *s1, char *s2, char terminal);
char	*slice(char *src, size_t start, size_t end);
char	**str_split(char *str, char *sep);
bool	is_space(int c);
void	init_str(char *str, int len);
void	print_str(int fd, char *str);
void	ft_strcpy(char *dst, char *src);
void	puterror(char *str);
size_t	ft_strlen(char *str);
int		count_str_array(char *arr[]);
void	init_str_array(char *arr[], int arr_len);
void	free_str_arr(char **arr);
char	**remove_str_arr(char **str_arr, int removed_index);
void	print_str_array(char **str_arr);
char	**add_str_arr(char **str_arr, char *new_str);
char	*str_join(char *s1, char *s2);
void	edit_str_arr(char **str_arr, int edited_index, char *new_str);
int		ft_atoi(char *nstr);
char	*itoa(int n);
int		is_equal(char *s1, char *s2);
int		is_include(char *str, char c);
char	**sort_arr(char **str);
#endif
