/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2024/01/11 11:38:00 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	t_command	cmd;
// 	t_list		*token_list;
// 	t_list		*cmd_list;
// 	char		*cmd_str;
// 	// pid_t		pid;
//
// 	cmd.env = envp;
// 	token_list = NULL;
// 	cmd_list = NULL;
//
// 		while (true)
// 		{
// 			// HACK: à laisser c'est le point d'insertion pour les
// test 			if (argc == 2)
// 			{
// 				tester_ms(argv[1], token_list, cmd_list);
// 				return (0);
// 			}
// 			cmd_str = display_prompt();
// 			token_list = tokenizer(cmd_str, token_list);
// 			cmd_list = parser(cmd_list, token_list);
// 			cmd_str = trim_str(cmd_str);
// 			add_history(cmd_str);
// 			if (strcmp(cmd_str, ""))
// 			{
// 				parse_cmd(cmd_str, &cmd);
// 				exec_cmd(cmd, envp);
// 			}
// 		}
// 		free(cmd_str);
// 		ft_lstclear(&token_list, free_token);
// 		ft_lstclear(&cmd_list, free_cmd);
// 		return (0);
// 	}
//

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd;
	t_list		*token_list;
	t_list		*cmd_list;
	char		*cmd_str;

	while (true)
	{
		token_list = NULL;
		cmd_list = NULL;
		cmd_str = display_prompt();
		add_history(cmd_str);
		log_printf("\nSTR = %s\n", cmd_str);
		token_list = tokenizer(cmd_str, token_list);
		ft_lstiter(token_list, &print_token);
		cmd_list = parser(cmd_list, token_list);
		ft_lstiter(cmd_list, &print_cmd);
    main_exec(cmd_list, envp);
    clean_process(token_list, cmd_list, cmd_str);
	}
  clean_process(token_list, cmd_list, cmd_str);
	return (0);
}
