#include "minishell.h"

static int	is_end_heredoc(char *end_str, char *str)
{
	size_t	i;

	if (str && str[0] == '\0')
	{
		write(1, "\n", 1);
		return (1);
	}
	if (!end_str || !str || ft_strlen(str) != ft_strlen(end_str) + 1)
		return (0);
	i = 0;
	while (i < ft_strlen(str) - 1 && end_str[i] == str[i])
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}

int	input_heredoc(char *end_str)
{
	int		read_byte;
	char	buffer[1024];
	int		p[2];

	pipe(p);
	while (1)
	{
		write(1, "> ", 3);
		read_byte = read(0, buffer, 1024);
		buffer[read_byte] = '\0';
		if (read_byte > 0 && find_index(buffer, '\n') == -1)
		{
			while (find_index(buffer, '\n') == -1)
			{
				write(p[1], buffer, read_byte);
				read_byte = read(0, buffer, 1024);
				buffer[read_byte] = '\0';
			}
		}
		if (is_end_heredoc(end_str, buffer))
			break ;
		write(p[1], buffer, read_byte);
	}
	close(p[1]);
	return (p[0]);
}
