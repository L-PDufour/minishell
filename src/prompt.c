/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:45:53 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/13 18:27:42 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*display_prompt(void)
{
	char	*path;
	char	*read_cmd;

	path = get_pwd();
	print_in_color(BOLD_YELLOW, "┌─[");
	print_in_color(BOLD_YELLOW, getenv("USER"));
	print_in_color(BOLD_YELLOW, "] - ");
	print_in_color(GREEN, path);
	print_in_color(BOLD_YELLOW, " \n│");
	print_in_color(BOLD_YELLOW, "\n└──────────> ");
	print_in_color(BOLD_BLUE, "🔥Ready... 🔥 ");
	read_cmd = readline("");
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

void	exec_cmd(t_command cmd, char **envp)
{
	int		i;
	char	*tmp;
	// char	**env_copy;
	i = 0;
	if (!strcmp(cmd.name, "pwd"))
		exec_pwd(cmd.option);
	else if (!strcmp(cmd.name, "cd"))
		change_dir(cmd.option);
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
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	else
	{
		print_in_color(RED, "🚨command not found: ");
		print_in_color(RED, cmd.name);
		printf("\n");
	}
}
