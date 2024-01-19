/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:20:32 by yothmani          #+#    #+#             */
/*   Updated: 2024/01/18 14:07:47 by yothmani         ###   ########.fr       */
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
	return (NULL);
}

void	exec_cmd(t_command cmd, char **envp)
{
	int		i;
	char	*old;
	char	**tmp;
	char	*cmd_path;
	pid_t	pid;

	i = 0;
	cmd.pid = pid;
	if (exec_builtin(cmd, cmd.env)) // si cest pas un builtin rentre dedans la condition
	{
		pid = fork();
		if (pid == -1)
			printf(" fork failed\n");
		if (pid == 0)
		{
			tmp = ft_split(cmd.cmd_str, ' ');
			cmd_path = get_cmd_path(tmp[0], envp);
			if (!cmd_path)
			{
				clean_table(tmp);
				print_in_color(RED, "🚨command not found:  ");
				print_in_color(RED, cmd.name);
				printf("\n");
				cmd.exit_status = 127;
				handle_exit_status(cmd);
				return ;
			}
			if (execve(cmd_path, tmp, cmd.env) == -1)
				cmd.exit_status = 1;
			else
				cmd.exit_status = 0;
			handle_exit_status(cmd);
		}
	}
	waitpid(pid, NULL, 0);
}


/**
 * une commande 
 * (echo) (bonjour) (|) (cat) (ls) (-la)
 * 
 * liste chainéee qui a été parsé et prete à etre éexécutée.
 * I- Builtin 
 * II-non-Builtin
 * 
 * 
 * execution (resultat)
 * 
 * 
*/