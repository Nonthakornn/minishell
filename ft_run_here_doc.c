#include "minishell.h"

size_t	ft_len(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int	ft_find_index(char *str, char c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	is_end_here_doc(char *end_str, char *str)
{
	int	i;
	int	j;

	if (str && str[0] == '\0')
		return (1);
	if (!end_str || !str || ft_len(str) != ft_len(end_str) + 1)
		return (0);
	i = 0;
	while (i < ft_len(str) - 1 && end_str[i] == str[i])
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}

static int	input_here_doc(char *end_str)
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
		if (read_byte > 0 && ft_find_index(buffer, '\n') == -1)
		{
			while (ft_find_index(buffer, '\n') == -1)
			{
				write(p[1], buffer, read_byte);
				read_byte = read(0, buffer, 1024);
				buffer[read_byte] = '\0';
			}
		}
		if (is_end_here_doc(end_str, buffer))
			break ;
		write(p[1], buffer, read_byte);
	}
	close(p[1]);
	return (p[0]);
}

static int	count_pipe(t_pipe *pipe_head)
{
	int		count;

	count = 0;
	while (pipe_head)
	{
		count++;
		pipe_head = pipe_head->next;
	}
	return count;
}

static int	count_here_doc_in_pipe(t_redirect *redir)
{
	int count;

	count = 0;
	while (redir)
	{
		if (redir->token_type == HERE_DOC)
			count++;
		redir = redir->next;
	}
	return count;
}

int	*run_here_doc_in_pipe(t_redirect *redir)
{
	int	*fds;
	int	redir_number;
	int	i;

	i = 0;
	fds = malloc(sizeof(int) * (count_here_doc_in_pipe(redir) + 1));
	fds[count_here_doc_in_pipe(redir)] = 0;
	while (redir)
	{
		if (redir->token_type == HERE_DOC)
		{
			fds[i] = input_here_doc(redir->value);
			i++;
		}
		redir = redir->next;
	}
	return fds;
}

int	**run_here_doc_in_cmd(t_pipe *pipe)
{
	t_redirect	*temp_redir;
	int			**here_doc_fds;
	int			i;

	here_doc_fds = malloc(sizeof(int *) * (count_pipe(pipe) + 1));
	here_doc_fds[count_pipe(pipe)] = NULL;
	i = 0;
	while (pipe)
	{
		here_doc_fds[i] = run_here_doc_in_pipe(pipe->redicts);
		pipe = pipe->next;
		i++;
	}
	return here_doc_fds;
}
