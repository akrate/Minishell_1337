/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:55:00 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/31 04:32:50 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_pos(char *str,int *i)
{
    char c;
    if (str[*i] == '\'' || str[*i] == '"')
    {
        c = str[*i];
        (*i)++;
        while (str[*i] && str[*i] != c)
            (*i)++;
        if (str[*i] == c)
            (*i)++;
    }else{
        while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != ' ' && is_meta(str[*i]) == 0)
            (*i)++;
    }
}
t_list *chr_meta(char *str,int *i)
{
    if (str[*i] == '<')
    {
        if (str[(*i) + 1] == '<')
        {
            if (str[(*i) + 2] == '<')
                return (write (1,"parse error\n",12),NULL);
            return ((*i) += 2,fill_node(ft_strdup("<<"),T_DLESS,1));
        }
        else
            return ((*i)++,fill_node(ft_strdup("<"),T_LESS,1));
    }else if (str[*i] == '>')
    {
        if (str[(*i) + 1] == '>')
        {
            if (str[(*i) + 2] == '>')
                return (write (1,"parse error\n",12),NULL);
            return ((*i) += 2,fill_node(ft_strdup(">>"),T_DGREAT,1));
        }
        else
            return ((*i)++,fill_node(ft_strdup(">"),T_GREAT,1));
    }else if (str[*i] == '|')
    {
        if (str[(*i) + 1] == '|')
            return (write (1,"parse error\n",12),NULL);
        return ((*i)++,fill_node(ft_strdup("|"),T_PIPE,1));
    }
    return (NULL);
}

t_list *split_cmd(char *str ,int flag)
{
    int i = 0;
    int start;
    t_list *head = NULL;

    if (!str)
        return NULL;
    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        if (str[i] == '\0')
            break;

        if (is_meta(str[i]))
        {
            if (ft_lstadd_back(&head, chr_meta(str, &i)) == 1)
                free_garbage(&(set_get_data(NULL)->lst_gc_g));
                // return (ft_lstclear(&head), NULL);
        }
        else
        {
            start = i;
            while (str[i] && !is_meta(str[i]) && str[i] != ' ')
                get_pos(str, &i);
            
            if (i > start)
            {
                if (ft_lstadd_back(&head, fill_node(ft_substr(str, start, i - start), T_IDENTIFIER, flag)) == 1)
                    free_garbage(&(set_get_data(NULL)->lst_gc_g));
                    // return (NULL);
            }
        }
    }
    return head;
}
// static void init_qouts(t_qout *strc)
// {
//     strc->i = 0;
//     strc->in_quote = 0;
//     strc->quote_char = 0;
//     strc->result = ft_strdup("");
//     strc->tmp = NULL;
// }
// char *skip_double_qout(char *str)
// {
//     t_qout qout;

//     init_qouts(&qout);

//     while (str[qout.i])
//     {
//         if (str[qout.i] == '"' && qout.in_quote == 0)
//         {
//             qout.in_quote = 1;
//             qout.quote_char = '"'; // Start double quote context
//             qout.i++; // Skip opening quote
//             continue;
//         }
//         if (str[qout.i] == '"' && qout.in_quote == 1)
//         {
//             qout.in_quote = 0;
//             qout.quote_char = 0; // End double quote context
//             qout.i++; // Skip closing quote
//             continue;
//         }

//         // Append current character to result
//         char *tmp = ft_substr(str, qout.i, 1);
//         char *new_res = ft_strjoin(qout.result, tmp);
//         qout.result = new_res;
//         qout.i++;
//     }

//     return qout.result;
// }


void paring_cmd(char *cmd)
{
    t_list *args;
    t_list *tmp;

    int flag;
    args = split_cmd(cmd,0);
    if (args == NULL)
        return;
    flag = 0;
    if (checking_cmd(&args) == 1)
        return ;
    tmp = convert_dolar2(&args);
    ft_lstclear(&args);
    while (tmp)
    {
        if (tmp->type == T_DLESS)
            flag = 2;
        if (flag == 0)  
            tmp->content = checking_dolar(tmp->content);
        if (tmp->content == NULL)
            ft_lstclear(&args);
        tmp->content = skip_qouts(tmp->content,tmp->remove_qoute);
        printf("[%s]-\n", (char *)tmp->content);
        if (flag != 0)
            flag--;
        tmp = tmp->next;
    }
}
