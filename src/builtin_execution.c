/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:11:27 by yothmani          #+#    #+#             */
/*   Updated: 2024/01/12 17:30:36 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_cmd(char *str_cmd, t_command *cmd)
{
	char	**tab_cmd;
	int		i;
	char	*tmp;

	tab_cmd = ft_split(str_cmd, ' ');
	if (!tab_cmd)
		return ;
	cmd->name = tab_cmd[0];
	cmd->option = "";
	cmd->option2 = "";
	cmd->cmd_str = str_cmd;
	if (!tab_cmd[1])
		return ;
	cmd->option = tab_cmd[1];
	i = 2;
	tmp = "";
	if (!tab_cmd[2])
		return ;
	while (tab_cmd[i])
	{
		if (tab_cmd[i])
			tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, tab_cmd[i]);
		i++;
	}
	cmd->option2 = tmp;
}

int	exec_builtin(t_command cmd, char **envp)
{
	int		i;
	char	*tmp;
	int		result;

	i = 0;
	if (!strcmp(cmd.name, "pwd"))
		exec_pwd(cmd.option);
	else if (!strcmp(cmd.name, "./minishell"))
		open_and_handle_new_terminal(cmd);
	else if (!strcmp(cmd.name, "cd"))
	{
		change_dir(cmd.option, &cmd);
		handle_exit_status(cmd);
		return 0;
	}
	else if (!strcmp(cmd.name, "exit"))
		exec_exit(&cmd);
	else if (!strcmp(cmd.name, "echo"))
		exec_echo(cmd);
	else if (!strcmp(cmd.name, "env"))
		exec_env(cmd);
	else
		return (1);
	cmd.exit_status=0;
	handle_exit_status(cmd);
	return (0);
}
