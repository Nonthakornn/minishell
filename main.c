#include "minishell.h"

ssize_t read_fd_until_end(int fd) {
    char buffer[1024];  // Buffer to store data
    ssize_t bytesRead;
    
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        // Write the buffer contents to standard output (or process the data as needed)
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    if (bytesRead == -1) {
        perror("read");
        return -1;  // Return -1 on error
    }

    return 0;  // Successfully reached the end of file
}

int main(int argc, char *argv[], char *env[])
{
	t_redirect	**redirect_head;

	t_redirect	*r11;
	t_redirect	*r12;
	t_redirect	*r13;
	t_redirect	*r21;
	t_pipe		*p1;
	t_pipe		*p2;
	int			**here_doc_fds;
	int			pid1;
	int			pid2;

	r11 = malloc(sizeof(t_redirect));
	r12 = malloc(sizeof(t_redirect));
	r13 = malloc(sizeof(t_redirect));
	r21 = malloc(sizeof(t_redirect));
	p1 = malloc(sizeof(t_pipe));
	p2 = malloc(sizeof(t_pipe));

	r11->token_type = HERE_DOC;
	r11->value = "end";
	r11->next = r12;

	r12->token_type = READ_FILE;
	r12->value = "file1";
	r12->next = r13;

	r13->token_type = WRITE_FILE;
	r13->value = "write";
	r13->next = NULL;

	r21->token_type = HERE_DOC;
	r21->value = "EOF";
	r21->next = NULL;

	char **cmd = malloc(sizeof(char *) * 2);

	cmd[0] = "cat";
	cmd[1] =  NULL;
	p1->cmd = cmd;
	p1->redicts = r11;
	p1->next= p2;

	p2->cmd = cmd;
	p2->next = NULL;
	p2->redicts = r21;

	here_doc_fds = run_here_doc_in_cmd(p1);
	pid1 = fork();
	if (pid1 == 0)
	{
		redirect_in_pipe(p1->redicts, here_doc_fds[0]);
		read_fd_until_end(0);
		close(here_doc_fds[0][0]);
		close(here_doc_fds[1][0]);
		free(cmd);
		free(here_doc_fds[0]);
		free(here_doc_fds[1]);
		free(here_doc_fds);
		free(r11);
		free(r12);
		free(r13);
		free(r21);
		free(p1);
		free(p2);
		exit(0);
	}
	// pid2 = fork();
	// if (pid2 == 0)
	// {
	// 	redirect_in_pipe(p2->redicts, here_doc_fds);
	// 	read_fd_until_end(0);
	// 	close(here_doc_fds[0]);
	// 	close(here_doc_fds[1]);
	// 	free(cmd);
	// 	free(here_doc_fds);
	// 	free(r1);
	// 	free(r2);
	// 	free(r3);
	// 	free(p1);
	// 	free(p2);
	// 	exit(0);
	// }
	close(here_doc_fds[0][0]);
	close(here_doc_fds[1][0]);
	free(cmd);
	free(here_doc_fds[0]);
	free(here_doc_fds[1]);
	free(here_doc_fds);
	free(r11);
	free(r12);
	free(r13);
	free(r21);
	free(p1);
	free(p2);
	return (0);
}