/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:36:21 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/30 14:56:26 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"






int dolar_chek(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if(str[i] == '$')
            return (1);
        i++;
    }
    return (0);
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
            if (dolar_chek(tmp[i]) == 1)
            {
                if(ft_lstadd_back(&list,fill_node(wrap_with_pattern(ft_substr(tmp[i],0,ft_strlen(tmp[i]))),T_IDENTIFIER,0)) == 1)
                return (ft_lstclear_dolar(&list,tmp),NULL);
            }else
                if(ft_lstadd_back(&list,fill_node(ft_substr(tmp[i],0,ft_strlen(tmp[i])),T_IDENTIFIER,0)) == 1)
                    return (ft_lstclear_dolar(&list,tmp),NULL);
        }
        i++;
    }
    return (list);
}

char *get_first_word(char *str)
{
    char **tmp;
    char *first;
    tmp = ft_split(str,' ');
    int i;
    
    i = 0;
    first = wrap_with_pattern(ft_strdup(tmp[0]));
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



char *handle_double_dollar(char *str, int *index)
{
    int start = *index;
    while (str[*index] == '$')
        (*index)++;
    (*index)--;

    char *substr = ft_substr(str, start, *index - start);
    // int len = strlen(substr);
    char *d_qout = wrap_with_pattern(substr);
    // if (!d_qout)
    // {
    //     free(substr);
    //     return NULL; 
    // }

    // d_qout[0] = '*';                 
    // strcpy(d_qout + 1, substr);
    // d_qout[len + 1] = '*';
    // d_qout[len + 2] = '\0';
    // free(substr);

    return d_qout;
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
            while (str[*index] && (ft_isalnum(str[*index]) || str[*index] == '_') && str[*index] != '$')
                (*index)++;
        }
    }

    return ft_substr(str, start, *index - start);
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
        if (dolr->var_value == NULL)
            dolr->to_add = ft_strdup("\"\"");
        else
            dolr->to_add = ft_strdup(dolr->var_value);
        dolr->result = ft_strjoin_free(dolr->result, dolr->to_add);
        dolr->result = ft_strjoin_free(dolr->result, ft_strdup(dolr->str + dolr->i));
    }
}
void process_regular_char_2(convert_d *dolr)
{
    dolr->str1 = ft_substr(dolr->str, dolr->i, 1);
    dolr->result = ft_strjoin_free(dolr->result, dolr->str1);
    dolr->i++;
}
void process_regular_char(convert_d *dolr)
{
    dolr->str1 = wrap_with_pattern(ft_substr(dolr->str, dolr->i, 1));
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
        else if (dolr->str[dolr->i] == '$' && (dolr->str[dolr->i + 1] != '\'' && dolr->str[dolr->i + 1] != '"') )
        {
            if (ft_isalpha(dolr->str[dolr->i + 1]) == 0 && dolr->str[dolr->i + 1] != '_')
            {
                process_regular_char_2(dolr);
                continue;
            }
            else 
            { 
                process_dollar_sign(dolr);
                break;
            }
        }
        else
            process_regular_char(dolr);
    }
}
int dolar_njma(char *str)
{
    int i;
    i = 0;
    while (str[i])
    {
        if (str[i] == '*' && str[i + 1] == '$')
            return (1);
        i++;
    }
    return (0);
}
// void remove_asterisks(char *str) {
    
//     int i;
//     int j;

//     i = 0;
//     j = 0;
//     while (str[i]) {
//         if (str[i] != '*') {
//             str[j++] = str[i];
//         }
//         i++;
//     }
//     str[j] = '\0';
// }
void process_node_content(convert_d *dolr)
{

    while (1)
    {
        
        init_struct_dolar(dolr);
        
        process_content_loop(dolr);
        if (dolr->result != NULL && *(dolr->result))
        {
            
            free(dolr->tmp->content);
            dolr->tmp->content = dolr->result;
        }
        else
            free(dolr->result);
        
        free(dolr->str);
        if (present_dolar(dolr->tmp->content) == 0)
            break;
    }
    if (has_pattern(dolr->tmp->content) == 1)
    {
       remove_pattern(dolr->tmp->content);
    }
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
        dolr.tmp = dolr.tmp->next; 
    }
}


// t_list *process_node_content2(char *str)
// {
//     int i;
//     int start;
//     int sp;
//     char qout;
//     char *result;
//     char *helper;
//     t_list *tmp;
//     t_list *lst;
//     tmp = NULL;
//     i = 0;
//     while (str[i])
//     {
//         if (str[i] == '"' || str[i] == '\'')
//         {
//             helper = extract_quoted_substring(str,&i,str[i]);
//             result = ft_strjoin_free(result,helper);
//         }
//         else if (str[i] == '$' && (ft_isalpha(str[i + 1]) == 1 || str[i + 1] == '_'))
//         {
//             start = ++i;
//             while (ft_isalnum(str[i]) == 1 ||  str[i] == '_' )
//                 i++;
//             helper = getenv(ft_substr(str,start,i - start - 1));
//             if (check_space(helper) == 1)
//             {
//                 if (helper[0] != ' ')
//                 {
//                     sp = 0;
//                     while (helper[sp] && helper[sp] != ' ' && is_meta(helper[sp]) == 0)
//                         sp++;
//                     result = ft_strjoin(result,ft_substr(helper,0,sp));
//                     ft_lstadd_back(&tmp,fill_node(result,T_IDENTIFIER,1));
//                     free(result);
//                     join_lists(&tmp,split_cmd(helper + sp));
//                     free(helper);
//                 }
//                 else
//                 {
//                     result = ft_strjoin(result,ft_substr(helper,0,sp));
//                     ft_lstadd_back(&tmp,fill_node(result,T_IDENTIFIER,1));
//                     free(result);
//                     join_lists(&tmp,split_cmd(helper + sp));
//                     free(helper);
//                 }
//             }
//         }
//         else 
//         {
//             result = ft_strjoin_free(result,ft_substr(str,i,1));
//         }
//     }
//     if (result != NULL && *result)
//     {
//         lst = ft_lastlist(tmp);
//         lst->content = ft_strjoin_free(lst->content,result);
//     }
//     return(tmp);
// }
// t_list *convert_dolar2(t_list **list)
// {
//     int i;
//     t_list *tmp;
//     while (*list)
//     {
//         if (present_dolar((*list)->content) == 0)
//         {
//             ft_lstadd_back(&tmp,(*list));
//         }else 
//         {
//             join_lists(&tmp,process_node_content2);
//         }
//         (*list) = (*list)->next;
//     }
//     return (tmp);
// }