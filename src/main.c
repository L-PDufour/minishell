/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/14 13:00:22 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd;
	t_list		*token_list;
	char		*cmd_str;

	while (true)
	{
		// HACK: à laisser c'est le point d'insertion pour les test
		if (argc == 2)
		{
			cmd_str = argv[1];
			token_list = tokenizer(cmd_str, token_list);
			while (token_list)
			{
				printf("%s\n", ((t_token *)token_list->content)->value);
				token_list = token_list->next;
			}
			return (0);
		}
		cmd_str = display_prompt();
		token_list = tokenizer(cmd_str, token_list);
		while (token_list)
		{
			printf("%s\n", ((t_token *)token_list->content)->value);
			token_list = token_list->next;
		}
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
