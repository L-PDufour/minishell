/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:56:45 by yothmani          #+#    #+#             */
/*   Updated: 2024/01/11 20:39:14 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	return (path);
}

void	exec_pwd(char *cmd)
{
	if (!strcmp(cmd, ""))
		printf("%s\n", get_pwd());
	else
		print_in_color(RED, "🚨pwd: too many arguments\n");
		
}
