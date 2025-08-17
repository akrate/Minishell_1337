/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:27:51 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/17 13:58:34 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_spcmd_nodes(t_spcmd *head)
{
	int count = 0;

	while (head)
	{
		count++;
		head = head->next;
	}
	return count;
}
int is_built_in(char *str)
{
    if (ft_strcmp(str,"echo") == 0)
        return (1);
    else if (ft_strcmp(str,"cd") == 0)
        return (1);
    else if (ft_strcmp(str,"pwd") == 0)
        return (1);
    else if (ft_strcmp(str,"export") == 0)
        return (1);
    else if (ft_strcmp(str,"unset") == 0)
        return (1);
    else if (ft_strcmp(str,"env") == 0)
        return (1);
    else if (ft_strcmp(str,"exit") == 0)
        return (1);
    return (0);
}
void print_env(t_env *env)
{
    while (env)
    {
        if (ft_strcmp(env->var,"?=") != 0)
        {   
            if (env->val[0] != '\0' || ft_strchr(env->var,'=') != NULL)
            printf("%s%s\n",env->var,env->val);
        }
        env = env->next;
    }
    check_env("?=","0",env);
}
void printf_pwd(t_env *env)
{
    char *str;

    str = getcwd(NULL,0);
    printf("%s\n",str);
    check_env("?=","0",env);
    free (str);
}

void ex_echo(t_spcmd *lst,t_env *env)
{
    int i;
    int option = 0;
    
    i = 1;
    if (lst->cmd[1] == NULL)
    {
        printf("\n");
        check_env("?=","0",env);
        return;
    }
    if(ft_strcmp(lst->cmd[1], "-n") == 0)
    {
        option = 1;
        i++;   
    }
    while (lst->cmd[i])
    {
        printf("%s",lst->cmd[i]);
        if (lst->cmd[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if(option == 0)
        printf("\n");
    check_env("?=","0",env);
}
int check_nber(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}
void ft_exit(char **cmd,t_env *env)
{
    char *str;
    int i;
    
    printf("exit\n");
    if (cmd == NULL || cmd[1] == NULL)
        str = ft_getenv("?",env);
    else if (cmd[2] != NULL)
    {
        str = ft_strdup("1");
        printf("exit: too many arguments\n");
    }
    else
    {
        if (check_nber(cmd[1]) == 1)
        {
            printf("exit: %s: numeric argument required\n",cmd[1]);
            str = ft_strdup("2");
        }
        else
            str = ft_strdup(cmd[1]);
    }
    if (!str)
        i = 0;
    else
        i = ft_atoi(str);     
    free_garbage(&(set_get_data(NULL)->lst_gc_env));
    free_garbage(&(set_get_data(NULL)->lst_gc_g));
    exit(i);
}
int ex_built_in(t_spcmd *lst,t_env **env)
{
    if (ft_strcmp(lst->cmd[0],"echo") == 0)
        ex_echo(lst,*env);
    else if (ft_strcmp(lst->cmd[0],"cd") == 0)
        ft_cd(lst,env);
    else if (ft_strcmp(lst->cmd[0],"pwd") == 0)
        printf_pwd(*env);
    else if (ft_strcmp(lst->cmd[0],"export") == 0)
        ft_export_hp(lst,env);
    else if (ft_strcmp(lst->cmd[0],"unset") == 0)
        ft_unset(lst,env);
    else if (ft_strcmp(lst->cmd[0],"env") == 0)
        print_env(*env);
    else if (ft_strcmp(lst->cmd[0],"exit") == 0)
        ft_exit(lst->cmd,*env);
    return (0);
}


int env_len(t_env *env)
{
    int count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return count;
}

char *str_join_var_val(t_env *env)
{
    char *tmp = ft_strjoin(env->var, env->val);
    return tmp;
}

char **env_to_array(t_env *env)
{
    int len = env_len(env);
    char **envp = malloc(sizeof(char *) * (len + 1));
    int i = 0;

    while (env)
    {
        envp[i] = str_join_var_val(env);
        env = env->next;
        i++;
    }
    envp[i] = NULL;
    return envp;
}
char *ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
    char *tmp = ft_strjoin(s1, s2);
    if (!tmp) return NULL;
    char *res = ft_strjoin(tmp, s3);
    // free(tmp);
    return res;
}

char *get_cmd_path(char *cmd, t_env *env)
{
    char *path_env = ft_getenv("PATH", env);
    char **paths;
    char *full_path;
    int i = 0;

    if (!path_env)
        return NULL;
    paths = ft_split(path_env, ':');
    if (!paths)
        return NULL;
    
    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            return ft_strdup(cmd);
        else
        {
            return NULL;
        }
    }

    while (paths[i])
    {
        full_path = ft_strjoin3(paths[i], "/", cmd); 
        if (access(full_path, X_OK) == 0)
        {

            return full_path;
        }
        // free(full_path);
        i++;
    }
    return NULL;
}
void update_exit_status(t_env *env, int status)
{
    char *exit_code;

    if (WIFEXITED(status))
        status = WEXITSTATUS(status);
    else
        status = 1;

    exit_code = ft_itoa(status);
    check_env("?=", exit_code, env);
    // free(exit_code);
}

void execute_external(t_spcmd *lst, t_env *env)
{
    pid_t pid;
    int status;
    char *cmd_path;
    char **envp;

    pid = fork();
    if (pid == 0)
    {
        cmd_path = get_cmd_path(lst->cmd[0], env);
        if (!cmd_path)
        {
            printf("%s: command not found\n", lst->cmd[0]);
            exit(127);
        }
        envp = env_to_array(env);
        execve(cmd_path, lst->cmd, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    else
    {
        waitpid(pid, &status, 0);
        update_exit_status(env, status);
    }
}
void handle_redirections(t_redir *redir)
{
    int fd;

    while (redir)
    {
        if (redir->type == REDIR_OUT)
        {
            fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror(redir->file);
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redir->type == REDIR_APPEND) 
        {
            fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                perror(redir->file);
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redir->type == REDIR_IN) 
        {
            fd = open(redir->file, O_RDONLY);
            if (fd < 0)
            {
                perror(redir->file);
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        redir = redir->next;
    }
}

void execute_pipeline(t_spcmd *list, t_env *env)
{
    int pipefd[2];
    pid_t pid;
    int fd_in = 0; 

    t_spcmd *curr = list;

    while (curr)
    {
        pipe(pipefd);

        pid = fork();
        if (pid == 0)
        {
            dup2(fd_in, STDIN_FILENO);
            if (curr->next)
                dup2(pipefd[1], STDOUT_FILENO);
            
            close(pipefd[0]);

            handle_redirections(curr->redir);

            if (is_built_in(curr->cmd[0]))
                ex_built_in(curr, &env);
            else
                execute_external(curr, env);

            exit(EXIT_SUCCESS);
        }
        else if (pid < 0)
            perror("fork");
        else
        {
            waitpid(pid, NULL, 0);
            close(pipefd[1]);
            fd_in = pipefd[0];
            curr = curr->next;
        }
    }
}

void ft_exuction(t_spcmd *list, t_env **env)
{
    if (count_spcmd_nodes(list) == 1 && list->redir == NULL)
    {
        if (is_built_in(list->cmd[0]))
            ex_built_in(list, env);
        else
            execute_external(list, *env);
    }
    else
    {
        execute_pipeline(list, *env);
    }
}
