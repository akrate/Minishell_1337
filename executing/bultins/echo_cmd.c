#include "../../minishell.h"

int is_n_option(char *str)
{
    int i;

    if(!str || str[0] != '-'|| str[1] != 'n')
        return 0;
    i = 2;
    while(str[i])
    {
        if(str[i] == 'n')
            return 0;
        i++;
    }
    return 1;
}
char *remove_quotes(char *str)
{
    
}
int print_echo(char **av)
{
    char *rm_arg;
    int i = 0;
    int j = 0;

    while(av[i] && is_n_option(av[i]))
    {
        j = 1;
        i++;
    }
    while(av[i])
    {
        rm_arg = remove_quotes(av[i])
        if(!rm_arg)
        {
            write(STDOUT_FILENO, rm_arg, ft_strlen(rm_arg));
            free(rm_arg);
        }
        if(av[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if(!j)
        write(STDOUT_FILENO, "\n", 1);
    return 0;

}
