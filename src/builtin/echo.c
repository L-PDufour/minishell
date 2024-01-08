/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:40:38 by joe_jam           #+#    #+#             */
/*   Updated: 2023/12/21 18:43:41 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_echo(t_command cmd)
{
	char	*tmp;

	if (!strcmp(cmd.option, "-n"))
		printf("%s", parse_env(cmd.option2));
	else
	{
		tmp = ft_strjoin(parse_env(cmd.option), parse_env(cmd.option2));
		printf("%s\n", tmp);
		free(tmp);
	}
	return (0);
}
