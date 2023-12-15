/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:47:40 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/14 20:24:50 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// typedef enum e_tokentype {
//   ALPHA_T,
//   REDIR_IN_T,
//   REDIR_OUT_T,
//   REDIR_AM_T,
//   PIPE_T,
//   HERE_DOC_T,
//
// } t_tokentype;

// cmd_creation(token_list);
// create the number of struct given by the number of pipes

void	check_syntax_error(const t_list *tmp)
{
	if (tmp->next && ((t_token *)tmp->next->content)->type != ALPHA_T)
	{
		printf("%s\n", "syntax error");
	}
}

void	token_parser(const t_list *token_list)
{
	const t_list	*tmp;
	t_tokentype		current_type;

	tmp = token_list;
	while (tmp)
	{
		current_type = ((t_token *)tmp->content)->type;
		if (current_type == REDIR_IN_T || current_type == REDIR_OUT_T
			|| current_type == REDIR_AP_T)
		{
			check_syntax_error(tmp);
		}
		tmp = tmp->next;
	}
}

// check if the syntax rules are ok

// 	printf("%s\n", ((t_token *)token_list->content)->value);
t_list	*parser(t_list *cmd_list, const t_list *token_list)
{
	token_parser(token_list);
	// cmd_creation(token_list);
	return (cmd_list);
}
