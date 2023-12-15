/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/15 13:31:14 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd;
	t_list		*token_list;
	t_list		*cmd_list;
	char		*cmd_str;

	while (true)
	{
		// HACK: à laisser c'est le point d'insertion pour les test
		if (argc == 2)
		{
			cmd_str = argv[1];
			log_printf("%s\n", argv[1]);
			token_list = tokenizer(cmd_str, token_list);
			cmd_list = parser(cmd_list, token_list);
			return (0);
		}
		// cmd_str = display_prompt();
		//   cmd_str = trim_str(cmd_str);
		//   add_history(cmd_str);
		//   if (strcmp(cmd_str, "")) {
		//     parse_cmd(cmd_str, &cmd);
		//     exec_cmd(cmd, envp);
		//   }
	}
	free(cmd_str);
	return (0);
}
