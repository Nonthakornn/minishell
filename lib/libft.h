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

#endif
