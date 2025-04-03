#include "minishell.h"

static int	input_heredoc(char *end_str)
{
	char	*input;
	int		p[2];

	pipe(p);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			print_str(1, "bash: warning: here-document at line delimited by end-of-file");
			break ;
		}
		if (is_equal(input, end_str))
			break ;
		write(p[1], input, ft_strlen(input));
		write(p[1], "\n", 1);
		free(input);
	}
	close(p[1]);
	return (p[0]);
}

static int	count_heredoc_in_process(t_redirect *redir)
{
	int	count;

	count = 0;
	while (redir)
	{
		if (redir->token_type == HERE_DOC)
			count++;
		redir = redir->next;
	}
	return (count);
}

static int	*exec_heredoc_in_process(t_redirect *redir)
{
	int	*fds;
	int	redir_number;
	int	i;

	i = 0;
	redir_number = count_heredoc_in_process(redir);
	fds = malloc(sizeof(int) * (redir_number + 1));
	fds[redir_number] = 0;
	while (redir)
	{
		if (redir->token_type == HERE_DOC)
		{
			fds[i] = input_heredoc(redir->value);
			i++;
		}
		redir = redir->next;
	}
	return (fds);
}

void	exec_heredoc(t_process *process)
{
	while (process)
	{
		process->here_doc = exec_heredoc_in_process(process->redirect);
		process = process->next;
	}
}
