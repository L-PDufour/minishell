/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/14 12:30:35 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd;
	char		*cmd_str;

	(void)argc;
	(void)argv;
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
