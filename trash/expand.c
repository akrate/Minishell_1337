
// t_list	*process_node_content2(char *str,t_env *lst)
// {
// 	t_pd	pd;

// 	init_pd(&pd);
// 	while (str[pd.i])
// 	{
// 		if (str[pd.i] == '"' || str[pd.i] == '\'')
// 		{
// 			pd.helper = extract_quoted_substring(str, &pd.i, str[pd.i]);
// 			pd.result = ft_strjoin(pd.result, pd.helper);
// 		}
// 		else if (str[pd.i] == '=' && str[pd.i + 1] != ' ')
// 		{
// 			pd.start = pd.i;
// 			while (str[pd.i] && str[pd.i] != ' ')
// 				pd.i++;
// 			pd.helper = ft_substr(str,pd.start,pd.i - pd.start);
// 			pd.helper = join_in_dqout(pd.helper);
// 			pd.result = ft_strjoin(pd.result, pd.helper);
// 		}
// 		else if (str[pd.i] == '$' && (ft_isalpha(str[pd.i + 1]) || (str[pd.i+ 1] == '_' || str[pd.i + 1] == '?')))
// 		{
// 			pd.start = ++pd.i;
// 			while (ft_isalnum(str[pd.i]) || (str[pd.i] == '_' || str[pd.i] == '?'))
// 				pd.i++;
// 			pd.env_name = ft_substr(str, pd.start, pd.i - pd.start);
// 			pd.env_val = ft_getenv(pd.env_name,lst);
// 			if (pd.env_val)
// 			{
// 				if (check_space(pd.env_val))
// 				{
// 					pd.sp = 0;
// 					while (pd.env_val[pd.sp] && pd.env_val[pd.sp] != ' ')
// 						pd.sp++;
// 					if (pd.sp > 0)
// 					{
// 						pd.first = ft_substr(pd.env_val, 0, pd.sp);
// 						pd.result = ft_strjoin(pd.result, pd.first);
// 						ft_lstadd_back(&pd.tmp, fill_node(ft_strdup(pd.result),
// 								T_WORD, 1));
// 						pd.result = ft_strdup("\0");
// 					}
// 					if (pd.env_val[pd.sp] != '\0')
// 					{
// 						if (pd.result[0] != '\0')
// 						{
// 							ft_lstadd_back(&pd.tmp, fill_node(pd.result,
// 									T_WORD, 0));
// 						}
// 						join_lists(&pd.tmp, split_cmd(pd.env_val + pd.sp, 1));
// 						pd.result = ft_strdup("");
// 					}
// 				}
// 				else
// 					pd.result = ft_strjoin(pd.result, ft_strdup(pd.env_val));
// 			}
// 		}
// 		else if (str[pd.i] == '$' && str[pd.i + 1] == '\'')
// 		{
// 			pd.i++;
// 			pd.helper = extract_quoted_substring(str, &pd.i, str[pd.i]);
// 			pd.result = ft_strjoin(pd.result, pd.helper);
// 		}
// 		else
// 		{
// 			pd.result = ft_strjoin(pd.result, ft_substr(str, pd.i, 1));
// 			pd.i++;
// 		}
// 	}
// 	if (pd.result && *pd.result)
// 		ft_lstadd_back(&pd.tmp, fill_node(pd.result, T_WORD, 0));
// 	return (pd.tmp);
// }