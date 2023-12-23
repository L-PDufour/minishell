/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:00:23 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/21 16:20:00 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "minishell.h"

typedef struct s_cmd
{
	char		**cmd_table;
	int			expandable;
	int			fd_input;
	int			fd_output;
	char		*outfile;
	char		*infile;
	int			pipe[2];
}				t_cmd;

char	*parse_env(char *str);
t_cmd	*cmd_creation(t_list **head);
void	check_syntax_error(const t_list *tmp, int identifier);
void	token_parser(const t_list *token_list);
t_list	*parser(t_list *cmd_list, const t_list *token_list);

#endif