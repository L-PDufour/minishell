/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:20:32 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/22 21:34:15 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	exec_cmd(t_command cmd, char **envp)
{
	int		i;
	char	*old;
	char	**tmp;
	char	*cmd_path;

	i = 0;
	init_builtin(&cmd);
	if (is_builtin(cmd.name, cmd.builtin))
		exec_builtin(cmd, cmd.env);
	else
	{
		tmp = ft_split(cmd.cmd_str, ' ');
		cmd_path = get_cmd_path(tmp[0], envp);
		if (!cmd_path)
			clean_table(tmp);
		if (execve(cmd_path, tmp, cmd.env) == -1)
		{
			print_in_color(RED, "🚨command not found: ");
			print_in_color(RED, cmd.name);
			printf("\n");
		}
	}
}
