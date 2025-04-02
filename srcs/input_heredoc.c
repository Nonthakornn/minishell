#include "minishell.h"

static void	loop_write(int p[2], char *end_str)
{
	char		*input;
	t_process	**head;
	char		***var;

	while (1)
	{
		input = readline("> ");
		if (!input || is_equal(input, end_str))
		{
			free(input);
			head = get_head();
			var = get_var();
			free_process_and_redir(*head);
			free_str_arr(*var);
			free(*get_hdpipe());
			break ;
		}
		write(p[1], input, ft_strlen(input));
		write(p[1], "\n", 1);
		free(input);
	}
}

static void	handle_code(int signum)
{
	(void)	signum;

	g_signal = 130;
}

int	input_heredoc(char *end_str)
{
	int	p[2];
	int	pid;

	pipe(p);
	set_hdin(p[0]);
	set_hdout(p[1]);
	signal(SIGINT, handle_code);
	pid = fork();
	if (pid == 0)
	{
		setup_signal_heredoc();
		loop_write(p, end_str);
		close(p[0]);
		close(p[1]);
		exit(0);
	}
	wait(NULL);
	close(p[1]);
	return (p[0]);
}
