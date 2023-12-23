/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:11:27 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/21 15:25:26 by yothmani         ###   ########.fr       */
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

void	init_builtin(t_command *cmd)
{
	cmd->builtin = safe_calloc(6, sizeof(char *));
	cmd->builtin[0] = "echo";
	cmd->builtin[1] = "cd";
	cmd->builtin[2] = "exit";
	cmd->builtin[3] = "env";
	cmd->builtin[4] = "./minishell";
	cmd->builtin[5] = "pwd";
}

bool	is_builtin(char *cmd_name, char **builtin_table)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (builtin_table[size])
		size++;
	while (i < size)
	{
		if (!strcmp(cmd_name, builtin_table[i]))
			return (true);
		i++;
	}
	return (false);
}

void	exec_builtin(t_command cmd, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!strcmp(cmd.name, "pwd"))
		exec_pwd(cmd.option);
	else if (!strcmp(cmd.name, "./minishell"))
		open_and_handle_new_terminal(cmd);
	else if (!strcmp(cmd.name, "cd"))
		change_dir(cmd.option, &cmd);
	else if (!strcmp(cmd.name, "exit"))
		exit(0);
	else if (!strcmp(cmd.name, "echo"))
	{
		if (!strcmp(cmd.option, "-n"))
			printf("%s", parse_env(cmd.option2));
		else
		{
			tmp = ft_strjoin(parse_env(cmd.option), parse_env(cmd.option2));
			printf("%s\n", tmp);
			free(tmp);
		}
	}
	else if (!strcmp(cmd.name, "env"))
	{
		while (cmd.env[i])
		{
			printf("%s\n", cmd.env[i]);
			i++;
		}
	}
}
