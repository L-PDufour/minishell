/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:56:45 by yothmani          #+#    #+#             */
/*   Updated: 2024/01/20 16:49:56 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(NULL, 0);
	return (path);
}

void	exec_pwd(t_cmd *cmd)
{
	char	*current_directory;

  current_directory = NULL;
	if (cmd->cmd_table[1] == NULL)
	{
		current_directory = get_pwd();
		printf("%s\n", current_directory);
		free(current_directory); // Free the memory allocated by getcwd
	}
	else
	{
		print_in_color(RED, "🚨pwd: too many arguments\n");
	}
}
