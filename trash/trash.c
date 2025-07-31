// #include "minishell.h"

// void check_pos(char *str ,char *c,int *i)
// {
//     while (str[*i])
//     {
//         if (str[*i] == *c && str[*i + 1] == ' ')
//             return ;
//         (*i)++;
//     }
//     if (str[*i + 1] != ' ')
//     {
//         while (str[*i])
//         {
//             if (str[*i + 1] == 34 || str[*i + 1] == 39)
//             {
//                 (*i)++;
//                 *c = str[*i];
//                 while (str[*i])
//                 {
//                     if (str[*i] == *c && str[*i + 1] == ' ')
//                         return ;
//                     (*i)++;
//                 }
//             }else if (str[*i] != ' ')
//             {
//                 while (str[*i] && str[*i] != ' ')
//                 {
//                     if (str[*i + 1] == 34 || str[*i + 1] == 39)
//                         break ;
//                     (*i)++;
//                 }
//                 return ;
//             }
//         }
//     }
// }
// t_list *fill_node(char *str, int start, int finish)
// {
//     t_list *new;
//     char *cmd;
//     int i = 0;

//     cmd = malloc((finish - start + 1) * sizeof(char));
//     while (start <= finish)
//     {
//         cmd[i] = str[start];
//         i++;
//         start++;
//     }
//     cmd[i] = '\0';
//     if (cheking_doubleqoutes(cmd) == 1)
//     {
//         printf("%s",cmd);
//         write (1,"sd qout\n",10);
//         exit (1);
//     }
//     if (cmd[0] == 34 || cmd[0] == 39)
//     {
//         char *str;
//         str = skip_qoutes(cmd);
//         new = ft_lstnew(str);
//         free (cmd);
//         return (new);
//     }
//     new = ft_lstnew(cmd);
//     return (new);
// }

// // t_list *split_cmd(char *str)
// // {
// //     int i = 0;
// //     int j;
// //     t_list *head = NULL;
// //     t_list *new;

// //     while (str[i])
// //     {
// //         while (str[i] == ' ')
// //             i++;

// //         if (!str[i])
// //             break ;

// //         j = i;
// //         while (str[i] && str[i] != ' ')
// //             i++;

// //         new = fill_node(str, j, i);
// //         ft_lstadd_back(&head, new);
// //     }
// //     return (head);
// // }

// char *skip_qoutes(char *str)
// {
//     char *result;
//     char qout;
//     int i;
//     int count;

//     i = 0;
//     count = 0;
//     qout = str[i];
//     while (str[i])
//     {
//         if (str[i] == qout)
//             count++;
//         i++;
//     }
//     result = (char *)malloc((i - count + 1) * sizeof(char));
//     if (!result)
//         exit(1);
//     i = 0;
//     count = 0;
//     while (str[i])
//     {
//         if(str[i] != qout)
//         {
//             result[count] = str[i];
//             count++;
//         }
//         i++;
//     }
//     result[count] = '\0';
//     return (result);
// }
// int cheking_doubleqoutes(char *str)
// {
// 	int i;
// 	int count;
// 	int pos;
// 	pos = 0;
// 	count = 0;
// 	i = 0;

// 	while (str[i])
// 	{
// 		if (str[i] == 34 || str[i] == 39)
// 		{
// 			if (pos == 0)
// 				pos = i;
//             if ((i == 0 || str[i - 1] != 92) && str[pos] == str[i])
// 					count++;
// 		}
// 		i++;
// 	}
// 	if (count % 2 == 0)
// 		return (0);
// 	else
// 		return (1);

// }
// t_list *split_cmd(char *s)
// {
//     t_list *head = NULL;
//     char *tmp = NULL;
//     int i = 0, j;

//     while (s[i])
//     {
//         while (s[i] == ' ')
//             i++;
//         tmp = NULL;
//         while (s[i] && s[i] != ' ')
//         {
//             if (s[i] == '"' || s[i] == '\'')
//             {
//                 char q = s[i++];
//                 j = i;
//                 while (s[i] && s[i] != q)
//                     i++;
//                 tmp = join(tmp, &s[j], i - j);
//                 if (s[i] == q)
//                     i++;
//             }
//             else
//             {
//                 j = i;
//                 while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\'')
//                     i++;
//                 tmp = join(tmp, &s[j], i - j);
//             }
//         }
//         if (tmp)
//             ft_lstadd_back(&head, ft_lstnew(tmp));
//     }
//     return (head);
// }
// ///////////////////////////////////////////////////
// int check_unclosed_quotes(const char *str)
// {
//     char quote = 0;

//     for (int i = 0; str[i]; i++)
//     {
//         if ((str[i] == '"' || str[i] == '\''))
//         {
//             if (!quote)
//                 quote = str[i]; // فتحنا اقتباس
//             else if (quote == str[i])
//                 quote = 0; // سكّرنا الاقتباس
//         }
//     }
//     return (quote != 0); // إذا بقي مفتوح، فيه خطأ
// }

// t_list *split_cmd(char *str)
// {
//     if (check_unclosed_quotes(str))
//     {
//         fprintf(stderr, "خطأ: علامة اقتباس غير مغلقة\n");
//         return (NULL);
//     }

//     int i = 0;
//     t_list *head = NULL;

//     while (str[i])
//     {
//         while (str[i] == ' ')
//             i++;
//         if (!str[i])
//             break ;

//         int start = i;
//         int len = 0;
//         char quote = 0;

//         // تعديل هنا لنتحقق من الاقتباسات داخل بعضها بشكل صحيح
//         while (str[i] && (quote || str[i] != ' '))
//         {
//             if ((str[i] == '"' || str[i] == '\''))
//             {
//                 if (!quote)
//                     quote = str[i];
//                 else if (quote == str[i])
//                     quote = 0;
//             }
//             i++;
//             len++;
//         }

//         char *arg = malloc(len + 1);
//         if (!arg)
//             return (NULL);

//         int k = 0;
//         quote = 0;
//         for (int j = 0; j < len; j++)
//         {
//             char c = str[start + j];
//             if ((c == '"' || c == '\''))
//             {
//                 if (!quote)
//                     quote = c;
//                 else if (quote == c)
//                     quote = 0;
//                 else
//                     arg[k++] = c;
//             }
//             else
//             {
//                 arg[k++] = c;
//             }
//         }
//         arg[k] = '\0';
//         ft_lstadd_back(&head, ft_lstnew(arg));
//     }
//     return (head);
// }

// ////////////////////////////////

// int cheking_doubleqoutes(char *str)
// {
//     int single_quote = 0;  // Flag للاقتباس المفرد '
//     int double_quote = 0;  // Flag للاقتباس المزدوج "
//     int i = 0;

//     while (str[i])
//     {
//         if (str[i] == '\'' && (i == 0 || str[i-1] != '\\'))
// إذا كان ' وما قبلهش
//             single_quote = !single_quote;  // غير الحالة (فتح/غلق)
//         else if (str[i] == '"' && (i == 0 || str[i-1] != '\\'))
// إذا كان " وما قبلهش
//             double_quote = !double_quote;  // غير الحالة (فتح/غلق)
//         i++;
//     }
//     return (single_quote || double_quote);  // يرجع 1 إذا كان في quote مفتوح
// }
// char *fill_node(char *str, int start, int finish)
// {
//     if (start < 0 || finish < start || !str)  // تحقق من الحدود
//         return (NULL);

//     char *cmd = malloc(finish - start + 2);  // +2 بسبب الـ null terminator
//     if (!cmd)
//         return (NULL);

//     int i = 0;
//     while (start <= finish && str[start])
//         cmd[i++] = str[start++];
//     cmd[i] = '\0';

//     if (cheking_doubleqoutes(cmd))  // إذا كان في quotes مفتوحة
//     {
//         free(cmd);  // نظف الذاكرة أولاً
//         return (NULL);
//     }
//     return (cmd);
// }
// t_list *split_cmd(char *str)
// {
//     if (!str) return (NULL);

//     t_list *head = NULL;
//     int i = 0;
//     int len = strlen(str);

//     while (i < len)
//     {
//         while (i < len && str[i] == ' ') i++;  // تجاوز المسافات

//         if (i >= len) break ;

//         int j = i;
//         char quote = 0;

//         if (str[i] == '\'' || str[i] == '"')
//             quote = str[i++];  // افتح quote

//         while (i < len)
//         {
//             if (quote && str[i] == quote && (i == 0 || str[i-1] != '\\'))
// إذا كان quote مغلق
//             {
//                 quote = 0;
//                 i++;
//             }
//             else if (!quote && (str[i] == ' ' || str[i] == '\''
// 		|| str[i] == '"'))
//                 break ;
//             i++;
//         }

//         char *node_str = fill_node(str, j, i - 1);
//         if (!node_str)
//         {
//             ft_lstclear(&head, free);  // نظف القائمة إذا كان في خطأ
//             return (NULL);
//         }
//         ft_lstadd_back(&head, ft_lstnew(node_str));
//     }
//     return (head);
// }

// // char *checking_dolar(char *str)
// // {
// //     int i;
// //     int cout;
// //     int dolar;
// //     int j;
// //     int len;
// //     char *result;

// //     cout = 0;
// //     dolar = 0;
// //     len = 0;
// //     while (str[len])
// //     {
// //         if (str[len] == '\'')
// //             cout = 1;
// //         if (str[len] == '$')
// //         {
// //             j = len;
// //             dolar = 1;
// //         }
// //         len++;
// //     }
// //     if (dolar == 1 && cout == 1)
// //     {
// //         i = j;
// //         while (str[j] && str[j] != ' ' && str[j] != '\'' && str[j] != '"')
// //             j++;
// //         result = ft_substr(str,0,i - 1);
// //         result = ft_strjoin(result,getenv(ft_substr(str , i + 1,j - i)));
// //         result = ft_strjoin(result ,ft_substr(str,j,len - j));
// //         return (result);
// //     }
// //     return (str);
// // }


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
//             continue ;
//         }
//         if (str[qout.i] == '"' && qout.in_quote == 1)
//         {
//             qout.in_quote = 0;
//             qout.quote_char = 0; // End double quote context
//             qout.i++; // Skip closing quote
//             continue ;
//         }

//         // Append current character to result
//         char *tmp = ft_substr(str, qout.i, 1);
//         char *new_res = ft_strjoin(qout.result, tmp);
//         qout.result = new_res;
//         qout.i++;
//     }

//     return (qout.result);
// }
// int check_empty_str(char *str)
// {
//     // int i;
//     if (ft_strlen(str) == 0)
//         return (1);
//     // while (str)
//     return (0);
// }

// char	*checking_dolar(char *str)
// {
// 	t_dolar	dolar;

// 	init_dolar(&dolar);
// 	while (str[dolar.i])
// 	{
// 		if (str[dolar.i] == '\'' && !dolar.in_double_quote)
// 		{
// 			dolar.in_single_quote = !dolar.in_single_quote;
// 			dolar.result = ft_strjoin(dolar.result, ft_substr(str, dolar.i, 1));
// 			dolar.i++;
// 		}
// 		else if (str[dolar.i] == '"' && !dolar.in_single_quote)
// 		{
// 			dolar.in_double_quote = !dolar.in_double_quote;
// 			dolar.result = ft_strjoin(dolar.result, ft_substr(str, dolar.i, 1));
// 			dolar.i++;
// 		}
// 		else if (str[dolar.i] == '$' && !dolar.in_single_quote
// 			&& dolar.in_double_quote)
// 		{
// 			if (!ft_isalnum(str[dolar.i + 1]))
// 			{
// 				dolar.result = ft_strjoin(dolar.result, ft_substr(str, dolar.i,
// 							1));
// 				dolar.i++;
// 				continue ;
// 			}
// 			dolar.start = ++dolar.i;
// 			while (str[dolar.i] && (ft_isalnum(str[dolar.i])
// 					|| str[dolar.i] == '_'))
// 				dolar.i++;
// 			dolar.var_name = ft_substr(str, dolar.start, dolar.i - dolar.start);
// 			dolar.var_value = getenv(dolar.var_name);
// 			if (dolar.var_value)
// 				dolar.result = ft_strjoin(dolar.result,
// 						ft_strdup(dolar.var_value));
// 		}
// 		else
// 		{
// 			dolar.result = ft_strjoin(dolar.result, ft_substr(str, dolar.i, 1));
// 			dolar.i++;
// 		}
// 	}
// 	return (dolar.result);
// }


// void parc_token(t_list *list)
// {
//     t_list *tmp;
//     t_spcmd *cmd;
//     t_spcmd *result;
//     int i;

//     tmp = list;
//     cmd = NULL;
//     result = NULL;
//     while (tmp)
//     {
//         if (!cmd)
//             init_parc(&cmd, &i);
//         if (tmp->type == T_WORD)
//             cmd->cmd[i++] = tmp->content;
//         else if (is_redirection(tmp->type) && tmp->next)
//         {
//             redir_lstadd_back(&cmd->redir, new_redir(tmp->type, tmp->next->content));
//             tmp = tmp->next;
//         }
//         else if (tmp->type == T_PIPE)
//         {
//             cmd->cmd[i] = NULL;
//             spcmd_lstadd_back(&result, cmd);
//             cmd = NULL;
//             tmp = tmp->next;
//             continue;
//         }
//         tmp = tmp->next;
//     }
//     if (cmd)
//     {
//         cmd->cmd[i] = NULL;
//         spcmd_lstadd_back(&result, cmd);
//     }
// }