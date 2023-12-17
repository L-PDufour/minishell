/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/16 19:31:19 by ldufour          ###   ########.fr       */
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
			print_token_list(token_list);
			cmd_list = parser(cmd_list, token_list);
			print_cmd_list(cmd_list);
			return (0);
		}
		cmd_str = display_prompt();
		token_list = tokenizer(cmd_str, token_list);
		print_token_list(token_list);           
			// Voir fichier logfile qui contient les info de la token et cmd list
		cmd_list = parser(cmd_list, token_list); // Voir commentaire ci dessous
		print_cmd_list(cmd_list);
		cmd_str = trim_str(cmd_str);
		add_history(cmd_str);
		if (strcmp(cmd_str, ""))
		{
			parse_cmd(cmd_str, &cmd);
			exec_cmd(cmd, envp);
		}
	}
	free(cmd_str);
	return (0);
}
/* cmd_str = "ceci est un test"
Command Table:
  ceci
  est
  un
  test
Expandable: 0
Input File: N/A
Output File: N/A
Input FD: 0
Output FD: 0
Pipe FDs: 0 (read) / 0 (write)
*/
