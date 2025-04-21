#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_cmd
{
    char *cmd;
    char *token;

} t_cmd;


#endif