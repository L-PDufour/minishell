/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2024/01/12 13:44:22 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd;
	t_list		*token_list;
	t_list		*cmd_list;
	char		*cmd_str;
	// pid_t		pid;

	cmd.env = envp;
	token_list = NULL;
	cmd_list = NULL;

		while (true)
		{
			cmd_str = display_prompt();
			// token_list = tokenizer(cmd_str, token_list);
			// cmd_list = parser(cmd_list, token_list);
			cmd_str = trim_str(cmd_str);
			add_history(cmd_str);
			if (strcmp(cmd_str, ""))
			{
				parse_cmd(cmd_str, &cmd);
				exec_cmd(cmd, envp);
			}
		}
		free(cmd_str);
		// ft_lstclear(&token_list, free_token);
		// ft_lstclear(&cmd_list, free_cmd);
		return (0);
	}


// int	main(int argc, char **argv, char **envp)
// {
// 	t_command	cmd;
// 	t_list		*token_list;
// 	t_list		*cmd_list;
// 	char		*cmd_str;

// 	int nb_process; 
// 	while (true)
// 	{
// 		token_list = NULL;
// 		cmd_list = NULL;
// 		cmd_str = display_prompt();
// 		add_history(cmd_str);
//     	log_printf("\nSTR = %s\n", cmd_str);
// 		token_list = tokenizer(cmd_str, token_list);
// 		ft_lstiter(token_list, &print_token);
// 		cmd_list = parser(cmd_list, token_list);
// 		update_cmd_list(cmd_list, envp);
// 		ft_lstiter(cmd_list, &print_cmd);
// 		nb_process = ft_lstsize(cmd_list);
		// process_fork(cmd_list, nb_process);
// 		ft_lstclear(&token_list, free_token);
// 		ft_lstclear(&cmd_list, free_cmd);
// 		free(cmd_str);
// 	}
// 	ft_lstclear(&token_list, free_token);
// 	ft_lstclear(&cmd_list, free_cmd);
// 	free(cmd_str);
// 	log_printf("END OF LOG");
// 	return (0);
// }
