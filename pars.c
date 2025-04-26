/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:55:00 by aoussama          #+#    #+#             */
/*   Updated: 2025/04/26 18:58:29 by aoussama         ###   ########.fr       */
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
        while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != ' ' && !is_meta(str[*i]))
            (*i)++;
    }
}
t_list *file_node(char *content,t_token_type t_type)
{
    t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
    node->type = t_type;
	node->next = NULL;
	return (node);
}
t_list *chr_meta(char *str,int *i)
{
    if (str[*i] == '<')
    {
        if (str[(*i) + 1] == '<')
        {
            if (is_meta(str[(*i) + 2]))
                return (write (1,"parse error\n",12),NULL);
            return ((*i) += 2,file_node(ft_strdup("<<"),T_DLESS));
        }
        else
            return ((*i)++,file_node(ft_strdup("<"),T_LESS));
    }else if (str[*i] == '>')
    {
        if (str[(*i) + 1] == '>')
        {
            if (is_meta(str[(*i) + 2]))
                return (write (1,"parse error\n",12),NULL);
            return ((*i) += 2,file_node(ft_strdup(">>"),T_DGREAT));
        }
        else
            return ((*i)++,file_node(ft_strdup(">"),T_GREAT));
    }else if (str[*i] == '|')
        return ((*i)++,file_node(ft_strdup("|"),T_PIPE));
}
t_list *split_cmd(char *str)
{
    int i;
    int start;
    char *meta;
    t_list *head = NULL;
    if (!str)
        return (NULL);
    i = 0;
    while (str[i] == ' ')
            i++;
    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        start = i;
        while (str[i] && str[i] != ' ' && !is_meta(str[i]))
            get_pos(str,&i);
        if (is_meta(str[i]))
            if (!ft_lstadd_back(&head,chr_meta(str,&i)))
                return (ft_lstclear(&head), NULL);
        else
            if(!ft_lstadd_back(&head,ft_lstnew(ft_substr(str,start,i - start))))
                return (ft_lstclear(&head), NULL); 
    }
    return (head);
}
void paring_cmd(char *cmd)
{
    t_list *args = split_cmd(cmd);
    
    t_list *tmp = args;
    if(!tmp)
        write (1,"error",5);
    while (tmp)
    {
        printf("arg: %s\n", (char *)tmp->content);
        tmp = tmp->next;
    }
}
