/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:45:53 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/18 21:00:49 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*print_colored_message(const char *user, const char *path)
{
	char	*message;

	message = (char *)malloc(1024);
	if (message == NULL)
		return (NULL);
	strcpy(message, "\033[1;33m┌─[\033[1;33m");
	strcat(message, user);
	strcat(message, "\033[1;33m]- \033[1;32m");
	strcat(message, path);
	strcat(message, " \n│\n└──────────> \033[1;34m🔥Ready... 🔥 \033[0m");
	return (message);
}

/**
 * in case i want to use the old prompt
		// print_in_color(BOLD_YELLOW, "┌─[");
	// print_in_color(BOLD_YELLOW, getenv("USER"));
	// print_in_color(BOLD_YELLOW, "] - ");
	// print_in_color(GREEN, path);
	// print_in_color(BOLD_YELLOW, " \n│");
	// print_in_color(BOLD_YELLOW, "\n└──────────> ");
	// print_in_color(BOLD_BLUE, "🔥Ready... 🔥 ");
*/

char	*display_prompt(void)
{
	char	*path;
	char	*read_cmd;
	char	*msg;

	path = get_pwd();
	msg = print_colored_message(getenv("USER"), path);
	read_cmd = readline(msg);
	return (read_cmd);
}

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
	int		idx;
	char	*tmp;
	char	*old;

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
		}
	}
	else if (!strcmp(cmd.name, "env"))
	{
		// update_env(&cmd, envp);
		// cmd.env_copy = copy_env(envp, &cmd);
		while (cmd.env[i])
		{
			printf("%s\n", cmd.env[i]);
			i++;
		}
		// clean_table(cmd.env_copy);
	}
	else
	{
		char **tmp;
		tmp = ft_split(cmd.cmd_str, ' ');
		char *cmd_path = get_cmd_path(tmp[0], envp);
	if (!cmd_path)
	{
		clean_table(tmp);
		printf("Failed1\n");
	}
		if(execve(cmd_path, tmp, cmd.env) == -1)
			printf("Failed2\n");
		// print_in_color(RED, "🚨command not found: ");
		// print_in_color(RED, cmd.name);
		// printf("\n");
	}
}
