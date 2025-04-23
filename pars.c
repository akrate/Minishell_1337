/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:55:00 by aoussama          #+#    #+#             */
/*   Updated: 2025/04/23 21:09:58 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cheking_doubleqoutes(char *str)
{
	int i;
	int count;
	int pos; 
	pos = 0;
	count = 0;
	i = 0;

	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (pos == 0)
				pos = i;
            if ((i == 0 || str[i - 1] != 92) && str[pos] == str[i])
			    count++;
		}
		i++;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
	
}
void check_pos(char *str ,char *c,int *i)
{
    while (str[*i])
    {
        if (str[*i] == *c && str[*i + 1] == ' ')
            return ;
        (*i)++;
    }
    // if (str[*i + 1] != ' ')
    // {      
    //     while (str[*i])
    //     {
    //         if (str[*i + 1] == 34 || str[*i + 1] == 39)
    //         {
    //             (*i)++;
    //             *c = str[*i];
    //             while (str[*i])
    //             {
    //                 if (str[*i] == *c && str[*i + 1] == ' ')
    //                     return ;
    //                 (*i)++;
    //             }
    //         }else if (str[*i] != ' ')
    //         {
    //             while (str[*i] && str[*i] != ' ')
    //             {
    //                 if (str[*i + 1] == 34 || str[*i + 1] == 39)
    //                     break; 
    //                 (*i)++;
    //             }
    //             return ;
    //         }
    //     }
    // }
}
t_list *split_cmd(char *str)
{
    int i = 0;
    int j;
    char sp;
    int k = 0;
    t_list *head = NULL;
    t_list *new;

    
    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        if (str[i] == 34 || str[i] == 39)
        {
            sp = str[i];
            j = i;
            i++;
            k = 0;
            // check_pos(str,&sp,&i);
            while (str[i])
            {
                if (str[i] == sp && k == 0)
                {
                    if (str[i + 1] == ' ')
                        break;
                    sp = str[i];
                    k = 1;
                }
                else if (str[i] == ' ' && sp != 34 && sp != 39)
                    break;
                i++;
            }
            new = fill_node(str, j, i);
            ft_lstadd_back(&head, new);
        }
        else
        {
            j = i;
            while (str[i] && str[i] != ' ')
                i++;
            if (j < i)
            {
                new = fill_node(str, j, i);
                ft_lstadd_back(&head, new);
            }
        }
        
    }
    return head;
}
char *skip_qoutes(char *str)
{
    char *result;
    char qout;
    int i;
    int count;
    
    i = 0;
    count = 0;
    qout = str[i];
    while (str[i])
    {
        if (str[i] == qout)
            count++;
        i++;
    }
    result = (char *)malloc((i - count + 1) * sizeof(char));
    if (!result)
        exit(1);
    i = 0;
    count = 0;
    while (str[i])
    {
        if(str[i] != qout)
        {
            result[count] = str[i];
            count++;
        }
        i++;
    }
    result[count] = '\0';
    return (result);
}
t_list *fill_node(char *str, int start, int finish)
{
    t_list *new;
    char *cmd;
    int i = 0;

    cmd = malloc((finish - start + 1) * sizeof(char));
    while (start <= finish)
    {
        cmd[i] = str[start];
        i++;
        start++;
    }
    cmd[i] = '\0';
    if (cheking_doubleqoutes(cmd) == 1)
    {
        printf("%s",cmd);
        write (1,"sd qout\n",10);
        exit (1);
    }
    if (cmd[0] == 34 || cmd[0] == 39)
    {
        char *str;
        str = skip_qoutes(cmd);
        new = ft_lstnew(str);
        free (cmd);
        return new;
    }
    new = ft_lstnew(cmd);
    return new;
}




// t_list *split_cmd(char *str)
// {
//     int i = 0;
//     int j;
//     t_list *head = NULL;
//     t_list *new;

//     while (str[i])
//     {
//         while (str[i] == ' ')
//             i++;

//         if (!str[i])
//             break;

//         j = i;
//         while (str[i] && str[i] != ' ')
//             i++;

//         new = fill_node(str, j, i);
//         ft_lstadd_back(&head, new);
//     }
//     return head;
// }


void paring_cmd(char *cmd)
{
    t_list *args = split_cmd(cmd);
    
    t_list *tmp = args;
    while (tmp)
    {
        printf("arg: %s\n", (char *)tmp->content);
        tmp = tmp->next;
    }
}