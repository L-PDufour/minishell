/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:51:44 by yothmani          #+#    #+#             */
/*   Updated: 2024/01/16 16:49:48 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_in_env(char *key, char **envp)
{
	int	i;

	i = 0;
	while (envp[i]!=NULL)
	{
		if (ft_strnstr(envp[i], key, ft_strlen(key)))
			return (i);
		i++;
	}
	return (-1);
}

void	open_and_handle_new_terminal(t_command cmd)
{
	int		idx;
	char	*old;

	idx = find_in_env("SHLVL", cmd.env);
	old = ft_substr(cmd.env[idx], 6, ft_strlen(cmd.env[idx]));
	cmd.env[idx] = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(old) + 1));
	execve("minishell", NULL, cmd.env);
}

void exec_env(t_command cmd)
{
	int	i;

	i = 0;
	while (cmd.env[i])
	{
		printf("%s\n", cmd.env[i]);
		i++;
	}
	
}
void	update_env(t_command *cmd, char *new_var)
{
	size_t	i;

	i = 0;
	while (cmd->env[i] != NULL)
		i++;
	cmd->env[i] = new_var;
	i++;
	cmd->env[i] = NULL;
}
