#include "../minishell.h"

void fork_process(t_shell *shell, int proc)
{
    int i = 0;
    int status = 0;
    int pid_index = 0;

    while (i < proc)
    {
        if (shell->cmd[i].builtin == 1)
        {
            execute_builtin(shell->cmd[i].cmd);
        }
        else if (shell->cmd[i].cmd)
        {
            shell->pid[pid_index] = fork();
            if (shell->pid[pid_index] == -1)
            {
                printf("Fork failed\n");
                exit(1);
            }
        }
    }
         
}
