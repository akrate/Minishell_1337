/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:57:39 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/17 13:58:21 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] && s2[i]) {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int check_env(char *var, char *val, t_env *lst) {
    int i;
    char *str1;
    char *str2;
    i = 0;
    srch(var, &i);  
    if (var[i] == '=')
        str2 = ft_substr(var, 0, i);
    else
        str2 = var;

    while (lst) {
        i = 0;
        srch(lst->var, &i);
        str1 = ft_substr(lst->var, 0, i);

        if (ft_strcmp(str2, str1) == 0) {
            if (val != NULL) {
                lst->var = ft_strdup_env(var);
                lst->val = ft_strdup_env(val);
            }
            return (1);
        }
        lst = lst->next;
    }
    return (0);
}

void ft_export_hp(t_spcmd *lst, t_env **env) {
    t_env *curr;
    int i;

    if (lst->cmd[1] == NULL) {
        curr = *env;
        while (curr) {
            if (ft_strcmp(curr->var,"?=") != 0) {
                if (ft_strchr(curr->var,'=') != NULL && curr->val[0] == '\0')
                    printf("declare -x %s\"\"\n", curr->var);
                else if (curr->val[0] == '\0')
                    printf("declare -x %s\n", curr->var);
                else
                    printf("declare -x %s\"%s\"\n", curr->var, curr->val);
            }
            curr = curr->next;
        }
        check_env("?=","0",*env);
        return;
    }
    i = 1;
    while (lst->cmd[i]) {
        ft_export(lst->cmd[i],env);
        i++;
    }
}

int is_valid_var_name(char *str) {
    int i = 0;
    if (!(ft_isalpha(str[0]) || str[0] == '_'))
        return 0;
    while (str[i] && str[i] != '=') {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
            return 0;
        i++;
    }
    return 1;
}

char *join_tokens_with_spaces(t_list *tokens) {
    size_t total_len = 0;
    t_list *tmp = tokens;
    while (tmp) {
        total_len += strlen(tmp->content) + 1;
        tmp = tmp->next;
    }
    char *result = malloc(total_len);
    if (!result) return NULL;
    result[0] = '\0';
    tmp = tokens;
    while (tmp) {
        strcat(result, tmp->content);
        if (tmp->next)
            strcat(result, " ");
        tmp = tmp->next;
    }
    return result;
}

void ft_export(char *str, t_env **env) {
    int i;
    char *var;
    char *val;

    if (!is_valid_var_name(str)) {
        printf("export: %s': not a valid identifier\n", str);
        check_env("?=", "1", *env);
        return;
    }

    i = 0;
    srch(str, &i);

    var = ft_substr(str, 0, i + 1);

    if (str[i] == '=') {
        val = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
        if (check_env(var, val, *env) == 1) {
            return;
        }
        ft_env_add_back(env, ft_env_new(var, val));
    } else {
        if (!check_env(var, NULL, *env)) {
            val = ft_strdup("");
            ft_env_add_back(env, ft_env_new(var, val));
        }
    }
    check_env("?=", "0", *env);
}

