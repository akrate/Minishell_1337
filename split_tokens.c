/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:13:39 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/07 19:50:00 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir *new_redir(t_token_type type, const char *file)
{
    t_redir *node;
    node = ft_malloc(sizeof(t_redir),&(set_get_data(NULL)->lst_gc_g));
    node->type = type;
    node->file = ft_strdup(file);
    node->next = NULL;
    return node;
}

int	ft_lstadd_back_prc(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (!lst || !new)
		return (1);
	new->next = NULL;
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}
void redir_lstadd_back(t_redir **lst, t_redir *new)
{
    t_redir *current;

    if (!lst || !new)
        return;
    if (!*lst)
    {
        *lst = new;
        return;
    }
    current = *lst;
    while (current->next)
        current = current->next;
    current->next = new;
}

static void init_parc(t_spcmd **cmd, int *i)
{
    *cmd = ft_malloc(sizeof(t_spcmd), &(set_get_data(NULL)->lst_gc_g));
    (*cmd)->cmd = ft_malloc(sizeof(char *) * 100, &(set_get_data(NULL)->lst_gc_g));
    (*cmd)->redir = NULL;
    (*cmd)->next = NULL;
    *i = 0;
}

static t_spcmd *parse_command_segment(t_list **tmp_ptr)
{
    t_list *tmp;
    t_spcmd *cmd;
    int i;

    init_parc(&cmd, &i);
    tmp = *tmp_ptr;
    while (tmp && tmp->type != T_PIPE)
    {
        if (tmp->type == T_WORD)
            cmd->cmd[i++] = ft_strdup(tmp->content);
        else if (is_redirection(tmp->type) && tmp->next)
        {
            redir_lstadd_back(&cmd->redir, new_redir(tmp->type, tmp->next->content));
            tmp = tmp->next;
        }
        tmp = tmp->next;
    }
    cmd->cmd[i] = NULL;
    *tmp_ptr = tmp;
    return cmd;
}

void spcmd_lstadd_back(t_spcmd **lst, t_spcmd *new_node)
{
    t_spcmd *temp;

    if (!lst || !new_node)
        return;

    if (*lst == NULL)
    {
        *lst = new_node;
        return;
    }

    temp = *lst;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;
}

void parc_token(t_list *list,t_env **env)
{
    t_list *tmp;
    t_spcmd *result;
    t_spcmd *cmd;

    tmp = list;
    result = NULL;
    while (tmp)
    {
        cmd = parse_command_segment(&tmp);
        spcmd_lstadd_back(&result, cmd);
        if (tmp && tmp->type == T_PIPE)
            tmp = tmp->next;
    }
    ft_exuction(result,env);
}

