/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:29:08 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/18 10:22:58 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

static int	check_syntax_error(const t_list *tmp, int identifier)
{
	if (identifier == REDIR_I)
	{
		if (tmp->next && ((t_token *)tmp->next->content)->type != ALPHA_T)
		{
			log_printf("syntax error near unexpected token `%c'\n", identifier);
			printf("syntax error near unexpected token `%c'\n", identifier);
			return (-1);
		}
	}
	else if (identifier == PIPE)
	{
		if (!tmp->next || !tmp->previous ||
			((t_token *)tmp->next->content)->type != ALPHA_T ||
			((t_token *)tmp->previous->content)->type != ALPHA_T)
		{
			log_printf("syntax error near unexpected token `%c'\n", identifier);
			printf("syntax error near unexpected token `%c'\n", identifier);
			return (-1);
		}
	}
	return (0);
}

// TODO: Error handling when syntax error
int	syntax_parser(const t_list *token_list)
{
	const t_list	*tmp;
	t_tokentype		current_type;
	int				flag;

	tmp = token_list;
	flag = 0;
	while (tmp)
	{
		if (tmp->content)
		{
			current_type = ((t_token *)tmp->content)->type;
			if (flag == 0 && (current_type == REDIR_IN_T
					|| current_type == REDIR_OUT_T || current_type == REDIR_AP_T
					|| current_type == HERE_DOC_T))
				flag = check_syntax_error(tmp, REDIR_I);
			else if (flag == 0 && current_type == PIPE_T)
				flag = check_syntax_error(tmp, PIPE);
		}
		tmp = tmp->next;
	}
	return (flag);
}
