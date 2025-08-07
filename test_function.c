/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:31:53 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/01 11:33:02 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*token_type_to_string(t_token_type type)
{
	if (type == T_WORD)
		return ("T_WORD");
	if (type == T_PIPE)
		return ("T_PIPE");
	if (type == T_DGREAT)
		return ("T_DGREAT");
	if (type == T_GREAT)
		return ("T_GREAT");
	if (type == T_HEREDOC)
		return ("T_HEREDOC");
	if (type == T_LESS)
		return ("T_LESS");
	return ("UNKNOWN");
}
