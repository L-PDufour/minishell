/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:40:38 by joe_jam           #+#    #+#             */
/*   Updated: 2024/01/20 07:57:00 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void exec_echo(t_cmd cmd) {
  char *tmp;

  if (!ft_strcmp(cmd.option, "-n"))
    printf("%s", parse_env2(cmd, cmd.option2));
  else {
    tmp = ft_strjoin(parse_env2(cmd, cmd.option), parse_env2(cmd, cmd.option2));
    printf("%s\n", tmp);
    free(tmp);
  }
}
