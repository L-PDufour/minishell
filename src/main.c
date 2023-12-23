/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/23 14:57:36 by ldufour          ###   ########.fr       */
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

// TODO:Bouette
// int main(int argc, char **argv, char **envp) {
//   t_command cmd;
//   t_list *token_list;
//   t_list *cmd_list;
//   char *cmd_str;
//   char **temp;
//
//   // pid_t		pid;
//   while (true) {
//     token_list = NULL;
//     cmd_list = NULL;
//     cmd_str = display_prompt();
//     log_printf("\nSTR = %s\n", cmd_str);
//     token_list = tokenizer(cmd_str, token_list);
//     ft_lstiter(token_list, &print_token);
//     cmd_list = parser(cmd_list, token_list);
//     temp = envp_path_creation_leon(envp);
//     path_verification(temp, (t_cmd *)cmd_list);
//     update_cmd_list(cmd_list, envp);
//     exec_leon(cmd_list);
//     log_printf("\n");
//     ft_lstiter(cmd_list, &print_cmd);
//     log_printf("END OF LOG", cmd_str);
//     free(cmd_str);
//     ft_lstclear(&token_list, free_token);
//     ft_lstclear(&cmd_list, free_cmd);
//   }
//   return (0);
// }

