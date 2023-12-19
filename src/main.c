/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/18 15:45:33 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command		cmd;
	static t_list	*token_list;
	static t_list	*cmd_list;
	char			*cmd_str;

	while (true)
	{
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
		if (strcmp(cmd_str, ""))
		{
			parse_cmd(cmd_str, &cmd);
			exec_cmd(cmd, envp);
		}
	}
	free(cmd_str);
	ft_lstclear(&token_list, free_token);
	// ft_lstclear(&cmd_list, free_cmd);
	return (0);
}
