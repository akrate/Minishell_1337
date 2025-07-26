/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:36:21 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/26 22:01:55 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int check_space(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == ' ')
        {
            return (1);
        }
        i++;
    }
    return (0);
}



void join_lists(t_list **a, t_list *b)
{
    if (!*a)
    {
        *a = b;
        return;
    }

    t_list *last = *a;
    while (last->next)
        last = last->next;

    last->next = b;
}


void free_split(char **tmp)
{
    int i = 0;
    if (!tmp)
        return;
    while (tmp[i])
        free(tmp[i++]);
    free(tmp);
}

t_list *create_list(char *str,int flag)
{
    char **tmp;
    t_list *list;
    int j;
    int i;

    tmp = ft_split(str,' ');
    if (tmp == NULL)
        return (NULL);
    i = flag;
    list = NULL;
    while (tmp[i])
    {
        if (is_meta(tmp[i][0]))
        {
            j = 0;
            if (ft_lstadd_back(&list,chr_meta(tmp[i],&j)) == 1)
                return (ft_lstclear_dolar(&list,tmp),NULL);
        }
        else
        {
            if(ft_lstadd_back(&list,fill_node(ft_substr(tmp[i],0,ft_strlen(tmp[i])),T_IDENTIFIER,0)) == 1)
                return (ft_lstclear_dolar(&list,tmp),NULL);
        }
        i++;
    }
    return (free_split(tmp),list);
}

char *get_first_word(char *str)
{
    char **tmp;
    char *first;
    tmp = ft_split(str,' ');
    int i;
    
    i = 0;
    first = ft_strdup(tmp[0]);
    while (tmp[i])
    {
        free(tmp[i]);
        i++;
    }
    free(tmp);
    return (first);
}

static void init_struct_dolar(convert_d *dolar)
{
    dolar->i = 0;
    dolar->result = ft_strdup("");
    dolar->str = ft_strdup(dolar->tmp->content);
    dolar->start = 0;
    dolar->flag = 0;
}
char *extract_quoted_substring(char *str, int *index, char quote_char)
{
    int start = (*index)++;
    while (str[*index] && str[*index] != quote_char)
        (*index)++;
    return ft_substr(str, start, *index - start);
}

char *handle_double_dollar(char *str, int *index)
{
    int start = *index;
    while (str[*index] == '$')
        (*index)++;
    (*index)--;
    return ft_substr(str, start, *index - start);
}

char *extract_var_name(char *str, int *index)
{
    int start = *index;

    if (str[*index] == '"') {
        (*index)++;
        while (str[*index] && str[*index] != '"' && (ft_isalpha(str[*index]) || str[*index] == '_'))
            (*index)++;
        (*index)++;
    }
    else {
        if (ft_isdigit(str[*index]))
            (*index)++;
        else {
            while (str[*index] && (ft_isalnum(str[*index]) || str[*index] == '_'))
                (*index)++;
        }
    }

    return skip_qouts(ft_substr(str, start, *index - start), 1);
}

void process_var_and_update_list(convert_d *dolr)
{
    dolr->str1 = extract_var_name(dolr->str, &dolr->i);
    dolr->var_value = getenv(dolr->str1);
    free(dolr->str1);
    if (dolr->var_value && check_space(dolr->var_value) == 1)
    {
        if (dolr->flag == 1)
        {
            free(dolr->tmp->content);
            dolr->tmp->content = get_first_word(dolr->var_value);
        }
        dolr->helper = dolr->tmp->next;
        dolr->tmp->next = create_list(dolr->var_value, dolr->flag);
        if (dolr->str[dolr->i] != '\0')
            ft_lstadd_back(&dolr->tmp->next, fill_node(ft_strdup(dolr->str + dolr->i), T_IDENTIFIER, 1));
        join_lists(&dolr->tmp->next, dolr->helper);
    }
    else
    {
        if (dolr->var_value)
            dolr->to_add = ft_strdup(dolr->var_value);
        else
            dolr->to_add = ft_strdup("");
        dolr->result = ft_strjoin_free(dolr->result, dolr->to_add);
        dolr->result = ft_strjoin_free(dolr->result, ft_strdup(dolr->str + dolr->i));
    }
}

void process_regular_char(convert_d *dolr)
{
    dolr->str1 = ft_substr(dolr->str, dolr->i, 1);
    dolr->result = ft_strjoin_free(dolr->result, dolr->str1);
    dolr->i++;
}

void process_dollar_sign(convert_d *dolr)
{
    if (dolr->str[dolr->i + 1] == '$')
    {
        dolr->str1 = handle_double_dollar(dolr->str, &dolr->i);
        dolr->result = ft_strjoin_free(dolr->result, dolr->str1);
    }
    if (dolr->i > 0)
    {
        free(dolr->tmp->content);
        dolr->tmp->content = ft_substr(dolr->str, 0, dolr->i);
    }
    else
    {
        dolr->flag = 1;
    }
    dolr->i++;
    process_var_and_update_list(dolr);
}

void process_quotes(convert_d *dolr)
{
    char quote_char;
    
    quote_char = dolr->str[dolr->i];
    dolr->str1 = extract_quoted_substring(dolr->str, &dolr->i, quote_char);
    dolr->result = ft_strjoin_free(dolr->result, dolr->str1);
}

void process_content_loop(convert_d *dolr)
{
    while (dolr->str[dolr->i])
    {
        if (dolr->str[dolr->i] == '"' || dolr->str[dolr->i] == '\'')
            process_quotes(dolr);
        else if (dolr->str[dolr->i] == '$')
        {
            process_dollar_sign(dolr);
            break;
        }
        else
            process_regular_char(dolr);
    }
}

void process_node_content(convert_d *dolr)
{
    init_struct_dolar(dolr);

    process_content_loop(dolr);

    if (dolr->result && *(dolr->result))
    {
        free(dolr->tmp->content);
        dolr->tmp->content = dolr->result;
    }
    else
        free(dolr->result);

    free(dolr->str);
}

void skip_t_dless(convert_d *dolr)
{
    if (dolr->tmp->type == T_DLESS) {
        if (dolr->tmp->next != NULL && dolr->tmp->next->next != NULL)
            dolr->tmp = dolr->tmp->next->next;
        else
            dolr->tmp = NULL;
    }
}

void convert_dolar(t_list **list)
{
    convert_d dolr;

    dolr.tmp = *list;
    while (dolr.tmp)
    {
        skip_t_dless(&dolr);
        if (dolr.tmp == NULL)
            break;
        process_node_content(&dolr);
        process_node_content(&dolr);

        dolr.tmp = dolr.tmp->next;
    }
}


// void convert_dolar(t_list **list)
// {
//     convert_d dolr;

//     dolr.tmp = *list;
//     while (dolr.tmp)
//     {
//         if (dolr.tmp->type == T_DLESS) {
//             if (dolr.tmp->next != NULL && dolr.tmp->next->next != NULL) {
//                 dolr.tmp = dolr.tmp->next->next;
//             } else {
//                 break;
//             }
//         }
//         init_struct_dolar(&dolr);
//         while (dolr.str[dolr.i])
//         {
//             if (dolr.str[dolr.i] == '"')
//             {
//                 dolr.start = dolr.i++;
//                 while (dolr.str[dolr.i] && dolr.str[dolr.i] != '"')
//                     dolr.i++;
//                 dolr.str1 = ft_substr(dolr.str, dolr.start, dolr.i - dolr.start + 1);
//                 dolr.result = ft_strjoin_free(dolr.result, dolr.str1);
//             }
//             else if (dolr.str[dolr.i] == '\'')
//             {
//                 dolr.start = dolr.i++;
//                 while (dolr.str[dolr.i] && dolr.str[dolr.i] != '\'')
//                     dolr.i++;
//                 dolr.str1 = ft_substr(dolr.str, dolr.start, dolr.i - dolr.start + 1);
//                 dolr.result = ft_strjoin_free(dolr.result, dolr.str1);
//             }
//             else if (dolr.str[dolr.i] == '$')
//             {
//                 if (dolr.str[dolr.i + 1] == '$')
//                 {
//                     dolr.start = dolr.i;
//                     while (dolr.str[dolr.i] == '$')
//                         dolr.i++;
//                     dolr.i--;
//                     dolr.str1 = ft_substr(dolr.str,dolr.start, dolr.i - dolr.start);
//                     dolr.result = ft_strjoin_free(dolr.result, dolr.str1);
//                 }
//                 if (dolr.i > 0)
//                 {
//                     free(dolr.tmp->content);
//                     dolr.tmp->content = ft_substr(dolr.str, 0,dolr.i);
//                 }
//                 else
//                     dolr.flag = 1;
//                 dolr.start = ++dolr.i;
//                 if (dolr.str[dolr.i] == '"')
//                 {
//                     dolr.i++;
//                     while (dolr.str[dolr.i] != '"' && dolr.str[dolr.i] && (ft_isalnum(dolr.str[dolr.i]) || dolr.str[dolr.i] == '_'))
//                         dolr.i++;
//                     dolr.str1 = ft_substr(dolr.str, dolr.start, dolr.i - dolr.start + 1);
//                     dolr.result = ft_strjoin_free(dolr.result, dolr.str1);
//                     dolr.i++;
//                     continue;
//                 }
//                 else
//                 {
//                     if (ft_isdigit(dolr.str[dolr.i]) == 1)
//                         dolr.i++;
//                     else
//                     {
//                         while (dolr.str[dolr.i] && (ft_isalnum(dolr.str[dolr.i]) || dolr.str[dolr.i] == '_'))
//                             dolr.i++;
//                     }
//                 }
//                 dolr.str1 = skip_qouts(ft_substr(dolr.str, dolr.start, dolr.i - dolr.start),1);
//                 dolr.var_value = getenv(dolr.str1);
//                 free(dolr.str1);
//                 if (dolr.var_value && check_space(dolr.var_value))
//                 {
//                     if (dolr.flag == 1)
//                     {
//                         free(dolr.tmp->content);
//                         dolr.tmp->content = get_first_word(dolr.var_value);
//                     }
//                     dolr.helper = dolr.tmp->next;
//                     dolr.tmp->next = create_list(dolr.var_value,dolr.flag);
//                     if (dolr.str[dolr.i] != '\0')
//                         ft_lstadd_back(&dolr.tmp->next, fill_node(ft_strdup(dolr.str + dolr.i), T_IDENTIFIER,1));/// dakchi li b9a mn node 
//                     join_lists(&dolr.tmp->next, dolr.helper);
//                     break;
//                 }
//                 else
//                 {
//                     if (dolr.var_value)
//                         dolr.to_add = ft_strdup(dolr.var_value);
//                     else
//                         dolr.to_add = ft_strdup("");              
//                     dolr.result = ft_strjoin_free(dolr.result, dolr.to_add);
//                     dolr.result = ft_strjoin_free(dolr.result,ft_strdup(dolr.str + dolr.i));
//                 }
//                 break;
//             }
//             else
//             {
//                 dolr.str1 = ft_substr(dolr.str, dolr.i, 1);
//                 dolr.result = ft_strjoin_free(dolr.result, dolr.str1);
//             }
//             dolr.i++;
//         }
//         if (dolr.result && *(dolr.result))
//         {
//             free(dolr.tmp->content);
//             dolr.tmp->content = dolr.result;
//         }
//         else
//             free(dolr.result);
//         dolr.tmp = dolr.tmp->next;
//         free(dolr.str);
//     }
// }
