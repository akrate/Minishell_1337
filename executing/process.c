#include "../minishell.h"

void exit_code(t_shell *shell, int proc)
{
    int i = 0;
    int status = 0;
    while (i < proc)
    {
        if (shell->pid[i] > 0) // check if the process ID is valid
        {
            waitpid(shell->pid[i], &status, 0); // wait for the child process to finish
            if (WIFEXITED(status)) // check if the child process exited normally
                g_last_exit_code = WEXITSTATUS(status); // get the exit status of the child process
        }
        i++;
    }
}
void run_child(t_shell *shell, int i, int status)
{
    shell->pid[status] = fork(); // create a new process
    if(shell->pid[status] < 0) // check if fork failed
    {
        perror("Fork failed"); // print error message
        exit(EXIT_FAILURE); // exit with failure status
    }
    if(shell->pid[status] == 0)
    {
        child(shell, i); // run child process
    }

}
int execute_builtin(t_shell *shell, int i)
{
    if(strcmp("cd", shell->cmd[i].cmd[0]) == 0)
        return (exec_cd(shell, i));
    return 0; // return 0 if not a builtin command
}
void fork_process(t_shell *shell, int proc)
{
    int i = 0;
    int status = 0;

    while (i < proc)
    {
        if (shell->cmd[i].cmd) //
        {
            if(shell->cmd[i].builtin == 1) // check if the command is a builtin
                g_last_exit_code = execute_builtin(shell, i); // execute builtin command
            else if (shell->cmd[i].cmd[0])
            {
                shell->child_run = 1; // set child_run to 1
                run_child(shell, i, status); // run child process
                status++;
            }
        }
        i++;
    }
    exit_code(shell, proc); // wait for all child processes to finish
    shell->child_run = 0; // reset child_run to 0

}
