/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:26:11 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/26 17:20:39 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_qouts(t_qout *strc)
{
    strc->i = 0;
    strc->in_quote = 0;
    strc->quote_char = 0;
    strc->result = ft_strdup("");
    strc->tmp = NULL;
}
char *remove_space_in_dqout(char *str)
{
    int i = 0;
    int j;
    int k = 0;
    char *result;
    char **tmp;

    if (!str || str[0] != '"')
        return (str);
    result = ft_strdup("");
    tmp = malloc(sizeof(char *));
    if (!tmp && !result)
        return (NULL);
    while (str[i])
    {
        while (str[i] == ' ' && str[i])
            i++;

        j = i;
        while (str[i] != ' ' && str[i])
            i++;
        if (i > j)
        {
            tmp[k++] = ft_substr(str, j, i - j);
            // result = ft_strjoin(result, tmp);
            // free(tmp);
        }
    }
    k = 0;
    while (tmp[k])
    {
        printf("tesssssst%s\n",tmp[k++]);
    }
    return (tmp[0]);
}

char *skip_qouts(char *str, int rm_qu)
{
    t_qout qout;

    if (!rm_qu)
        return (str);
    init_qouts(&qout);
    while (str[qout.i])
    {
        if ((str[qout.i] == '\'' || str[qout.i] == '"') && qout.in_quote == 0)
        {
            qout.in_quote = 1;
            qout.quote_char = str[qout.i];
            qout.i++;
            continue;
        }
        if (str[qout.i] == qout.quote_char && qout.in_quote == 1)
        {
            qout.in_quote = 0;
            qout.quote_char = 0;
            qout.i++;
            continue;
        }
        qout.tmp = ft_substr(str, qout.i, 1);
        qout.result = ft_strjoin_free(qout.result, qout.tmp);
        qout.i++;
    }
    return qout.result;
}

int checking_cmd(t_list **list)
{
    t_list *lst;

    lst = *list;
    if (lst->type == T_PIPE)
    {
        write(2, "Error: command must end with identifier\n", 41);
        ft_lstclear(list);
        return (1);
    }
    while (lst)
    {
        if (checking_close_qoutes(lst->content) == 1)
        {
            write(2, "Error: unclosed quotes found\n", 29);
            ft_lstclear(list);
            return (1);
        }
        if (lst->next == NULL)
        {
            if (lst->type == T_PIPE)
            {
                write(2, "Error: command must end with identifier\n", 41);
                ft_lstclear(list);
                return (1);
            }
        }
        lst = lst->next;
    }
    return (0); 
}
