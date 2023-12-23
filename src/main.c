/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/22 21:07:01 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd;
	t_list		*token_list;
	t_list		*cmd_list;
	char		*cmd_str;
	// pid_t		pid;

	token_list = NULL;
	cmd_list = NULL;
	
		while (true)
		{
			// HACK: à laisser c'est le point d'insertion pour les test
			if (argc == 2)
			{
				tester_ms(argv[1], token_list, cmd_list);
				return (0);
			}
			cmd_str = display_prompt();
			token_list = tokenizer(cmd_str, token_list);
			cmd_list = parser(cmd_list, token_list);
			cmd_str = trim_str(cmd_str);
			add_history(cmd_str);
			if (ft_strcmp(cmd_str, ""))
			{
				parse_cmd(cmd_str, &cmd);
				exec_cmd(cmd, envp);
			}
		}
		free(cmd_str);
		ft_lstclear(&token_list, free_token);
		ft_lstclear(&cmd_list, free_cmd);
		return (0);
	}
