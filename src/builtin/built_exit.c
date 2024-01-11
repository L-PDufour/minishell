/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:50:09 by joe_jam           #+#    #+#             */
/*   Updated: 2024/01/11 16:47:05 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_numeral(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	exit_value(t_command *cmd)
{

	if (ft_strcmp(cmd->option2, ""))
	{
		printf("exit: too many arguments\n");
		cmd->exit_status = 1;
	}
	else if (cmd->option)
	{
		if (is_numeral(cmd->option))
		{
			cmd->exit_status = ft_atoi(cmd->option);
			while (cmd->exit_status < 0 || cmd->exit_status > 255)
			{
				if (cmd->exit_status < 0)
					cmd->exit_status += 256;
				else if (cmd->exit_status > 255)
					cmd->exit_status -= 256;
			}
		}
		else
		{
			printf("exit: %s: numeric argument required\n", cmd->option);
			cmd->exit_status = 255;
		}
	}
	return (cmd->exit_status);
}

	void exec_exit(t_command *cmd)
	{
		int result;

		if (!ft_strcmp(cmd->name, "exit"))
		{
			cmd->exit_status = exit_value(cmd);
			// exit(cmd->exit_status);
			printf("executing exit with value : %i\n", cmd->exit_status);
			handle_exit_status(*cmd);
		}
	}

	char **update_env(char **env, const char *new_var)
	{
		size_t env_size;
		size_t i;
		char **new_env;

		env_size = 0;
		i = 0;
		while (env[env_size] != NULL)
			env_size++;
		new_env = malloc((env_size + 2) * sizeof(char *));
		if (!new_env)
			return (NULL);
		while (i < env_size)
		{
			new_env[i] = env[i];
			i++;
		}
		new_env[env_size] = ft_strdup(new_var);
		new_env[env_size + 1] = NULL;
		// clean_table(env);
		return (new_env);
	}

	void handle_exit_status(t_command cmd)
	{
		int idx;
		char *old;
		char *new_var;

		idx = find_in_env("?", cmd.env);
		if (idx != -1)
		{
			old = ft_substr(cmd.env[idx], 2, ft_strlen(cmd.env[idx]));
			cmd.env[idx] = ft_strjoin("?=", ft_itoa(cmd.exit_status));
			free(old);
		}
		else
		{
			new_var = ft_strjoin("?=", ft_itoa(cmd.exit_status));
			cmd.env = update_env(cmd.env, new_var);
			free(new_var);
		}
	}
