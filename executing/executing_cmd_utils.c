#include "../minishell.h"



void init_cmd2(t_shell *shell, int i)
{
    shell->cmd[i].sts = 0;
    shell->cmd[i].redirin = -1;
    shell->cmd[i].redirout = -1;
    shell->cmd[i].cmd = exec_dir(shell, i);
    if (!shell->cmd[i].cmd)
        shell->cmd[i].cmd = 0;
    if(shell->cmd[i].cmd)
    {
        shell->cmd[i].path = shell->cmd[i].cmd[0];
        shell->cmd[i].builtin = check_cmd(shell->cmd[i].cmd[0]);
    }
}
void init_cmd(t_shell *shell, int proc)
{
    int i = 0;
    while(i < proc)
    {
        shell->cmd[i].index = i;
        shell->cmd[i].cmd = get_cmd(shell->ap[i]);
        if(!shell->cmd[i].cmd)
        {
            printf("Memory allocation failed\n");
        }
        else
        {
            shell->cmd[i].input_fd = 0;
            shell->cmd[i].output_fd = 1;
        }
        init_cmd2(shell, i);
        i++;
    }
}