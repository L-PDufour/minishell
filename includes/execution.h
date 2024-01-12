/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:03:20 by yothmani          #+#    #+#             */
/*   Updated: 2024/01/11 20:50:27 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

void	exec_cmd(t_command cmd, char **envp);
int		exec_builtin(t_command cmd, char **envp);
void		exec_pwd(char *cmd);
void		exec_env(t_command cmd);
void		exec_echo(t_command cmd);
// void	exec_non_builtin(t_command cmd, char **envp);
#endif
