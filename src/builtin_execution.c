/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:33:01 by yothmani          #+#    #+#             */
/*   Updated: 2024/01/20 16:59:01 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void parse_cmd(char *str_cmd, t_cmd *cmd) {
//   char **tab_cmd;
//   int i;
//   char *tmp;
//
//   tab_cmd = ft_split(str_cmd, ' ');
//   if (!tab_cmd)
//     return;
//   cmd->name = tab_cmd[0];
//   cmd->option = "";
//   cmd->option2 = "";
//   cmd->cmd_str = str_cmd;
//   if (!tab_cmd[1])
//     return;
//   cmd->option = tab_cmd[1];
//   i = 2;
//   tmp = "";
//   if (!tab_cmd[2])
//   return;
//   while (tab_cmd[i]) {
//     if (tab_cmd[i])
//       tmp = ft_strjoin(tmp, " ");
//     tmp = ft_strjoin(tmp, tab_cmd[i]);
//     i++;
//   }
//   cmd->option2 = tmp;
// }

int exec_builtin(t_cmd *cmd, char **envp) {

  if (!ft_strcmp(cmd->cmd_table[0], "pwd"))
    exec_pwd(cmd);
  else if (!ft_strcmp(cmd->cmd_table[0], "./minishell"))
    open_and_handle_new_terminal(cmd);
  // else if (!ft_strcmp(cmd->cmd_table[0], "cd")) {
  //   change_dir(cmd->option, cmd);
  //   handle_exit_status(*cmd);
  //   return 0;
  // } else if (!ft_strcmp(cmd->cmd_table[0], "export")) {
  //   export_exec(cmd);
  //   handle_exit_status(*cmd);
  //   return (0);
  // } else if (!ft_strcmp(cmd->cmd_table[0], "env")) {
  //   exec_env(cmd);
  //   handle_exit_status(*cmd);
  //   return (0);
  // } else if (!ft_strcmp(cmd->cmd_table[0], "exit"))
  //   exec_exit(cmd);
  // else if (!ft_strcmp(cmd->cmd_table[0], "echo"))
  //   exec_echo(*cmd);
  // else if (!ft_strcmp(cmd->cmd_table[0], "unset"))
  //   exec_unset(cmd);
  // else
  //   return (1);
  // cmd->exit_status = 0;
  // handle_exit_status(*cmd);
  return (0);
}
