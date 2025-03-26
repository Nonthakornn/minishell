#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>

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
char	*slice(char *src, size_t start, size_t end);
char	**str_split(char *str, char *sep);
void	print_str(int fd, char *str);
void	puterror(char *str);
char	*new_str(int len);
void	ft_strcpy(char *dst, char *src);
int		ft_strcmp(char *s1, char *s2, char terminal);
size_t	ft_strlen(char *str);
int		find_index(char *str, char c);
int		is_equal(char *s1, char *s2);
int		is_include(char *str, char c);
bool	is_space(int c);
int		startwith(char *str, char *word);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s1);
int		ft_isalnum(int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strcat(char *dst, char *src);
char	**malloc_array(int cmd_count);
#endif
