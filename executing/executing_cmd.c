#include "../minishell.h"
int cnt_string(char **str)
{
    int i = 0;
    while(str[i])
        i++;
    return i;
}

int nbr_of_pid(t_shell *shell, int proc)
{
    int i;
    int pid;

    i = 0;
    pid = 0;
    while(i < proc)
    {
        if(shell->cmd[i].cmd && shell->cmd[i].builtin == 0)
            pid++;
        i++;
    }
    return pid;
}
int *create_pid(int pid)
{
    int *pids;

    pids = NULL;
    if(pid > 0)
    {
        pids = malloc(sizeof(int) * sizeof(pid));
        if(!pids)
        {
            printf("Memory allocation failed\n");
            return NULL;
        }
    }
    return pids;
}

void execute_cmd(t_shell *shell)
{
    int proc = cnt_string(shell->ap);
    int pipes = proc - 1;

    shell->pipes = pipes;
    shell->fds = NULL;
    shell->pid = NULL;
    shell->cmd = calloc(proc, sizeof(t_command));
    if (!shell->cmd)
    {
        printf("Memory allocation failed\n");
    }
    init_cmd(shell, proc);
    if(nbr_of_pid(shell, proc) > 0)
        shell->pid = create_pid(nbr_of_pid(shell, proc));
    fork_process(shell, proc);
}
