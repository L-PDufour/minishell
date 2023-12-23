/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:11:27 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/22 20:33:10 by ldufour          ###   ########.fr       */
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

	i = 0;
	if (!ft_strcmp(cmd.name, "pwd"))
		return(exec_pwd(cmd.option));
	else if (!ft_strcmp(cmd.name, "./minishell"))
		return(open_and_handle_new_terminal(cmd));
	else if (!ft_strcmp(cmd.name, "cd"))
		return (change_dir(cmd.option, &cmd), 0);
	else if (!ft_strcmp(cmd.name, "exit"))
		return(exec_exit(cmd));
	else if (!ft_strcmp(cmd.name, "echo"))
		return (exec_echo(cmd));
	else if (!ft_strcmp(cmd.name, "env"))
		return (exec_env(cmd));
	return (1);
}
