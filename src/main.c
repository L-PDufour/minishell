/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/14 19:49:52 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd;
	t_list		*token_list;
	char		*cmd_str;

	cmd.env = envp;
	cmd.env[find_in_env("OLDPWD", cmd.env)]="OLDPWD=";
	while (true)
	{
		cmd_str = display_prompt();
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

// 	// HACK: à laisser c'est le point d'insertion pour les test
// 	if (argc == 2)
// 	{
// 		cmd_str = argv[1];
// 		token_list = tokenizer(cmd_str, token_list);
// 		while (token_list)
// 		{
// 			printf("%s\n", ((t_token *)token_list->content)->value);
// 			token_list = token_list->next;
// 		}
// 		return (0);
// 	}
// token_list = tokenizer(cmd_str, token_list);
// while (token_list)
// {
// 	printf("%s\n", ((t_token *)token_list->content)->value);
// 	token_list = token_list->next;
// }