#include "minishell.h"

bool    check_n(char *cmd)
{
    if (cmd[0] == '-')
        return (true);
    return (false);
}


int    exec_echo(t_process *process, char **variable)
{
    int    i;
    int first_word;
    char **cmd;

    i = 1;
    first_word = 1;
    cmd = process->cmd;
    // if (check_n(cmd[1]))
    // {
    //     printf("OK");
    // }

    while (cmd[i])
    {
        if (!first_word)
            printf(" ");
        else
            first_word = 0;
        printf("%s", cmd[i]);
        i++;
    }
    printf("\n");
    return (0);
}
