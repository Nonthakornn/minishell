#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

char	*itoa(int n);
int		ft_atoi(char *nstr);

char	**add_str_arr(char **str_arr, char *new_str);
char	**rm_str_arr(char **str_arr, int removed_index);
char	**sort_str_arr(char **str);
char	**new_str_arr(int arr_len);
int		count_str_arr(char *arr[]);
void	free_str_arr(char **arr);
void	edit_str_arr(char **str_arr, int edited_index, char *new_str);
void	print_str_arr(char **str_arr);

char	*str_join(char *s1, char *s2);

char	**str_split(char *str, char *sep);

int		find_index(char *str, char c);
int		ft_strcmp(char *s1, char *s2, char terminal);
char	*slice(char *src, size_t start, size_t end);
bool	is_space(int c);
char	*new_str(int len);
void	print_str(int fd, char *str);
void	ft_strcpy(char *dst, char *src);
void	puterror(char *str);
size_t	ft_strlen(char *str);
int		startwith(char *str, char *word);
int		is_equal(char *s1, char *s2);
int		is_include(char *str, char c);
#endif
