/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:50:09 by joe_jam           #+#    #+#             */
/*   Updated: 2024/01/10 17:56:56 by joe_jam          ###   ########.fr       */
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
	int	result;

	result = 0;
	if (ft_strcmp(cmd->option2, ""))
	{
		printf("exit: too many arguments\n");
		result = 1;
	}
	else if (cmd->option)
	{
		if (is_numeral(cmd->option))
			result = ft_atoi(cmd->option);
		else
		{
			printf("exit: %s: numeric argument required\n", cmd->option);
			result = 255;
		}
	}
	return (result);
}

void	exec_exit(t_command *cmd)
{
	int	result;

	if (!ft_strcmp(cmd->name, "exit"))
	{
		result = exit_value(cmd);
		printf("%i\n", result);
		exit(result);
	}
}

char	**update_env(char **array, const char *new_element)
{
	size_t	array_size;
	size_t	i;
	char	**new_array;

	array_size = 0;
	i = 0;
	while (array[array_size] != NULL)
		array_size++;
	new_array = (char **)malloc((array_size + 2) * sizeof(char *));
	if (new_array == NULL)
		return (NULL);
	while (i < array_size)
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[array_size] = ft_strdup(new_element);
	new_array[array_size + 1] = NULL;
	free(array);
	return (new_array);
}

void	handle_exit_status(t_command cmd)
{
	int		idx;
	char	*old;
	char	*new_var;

	idx = find_in_env("?", cmd.env);
	if (idx != -1)
	{
		old = ft_substr(cmd.env[idx], 2, ft_strlen(cmd.env[idx]));
		cmd.env[idx] = ft_strjoin("?=", ft_itoa(exit_value(&cmd)));
		free(old);
	}
	else
	{
		new_var = ft_strjoin("?=", ft_itoa(exit_value(&cmd)));
		cmd.env = update_env(cmd.env, new_var);
		free(new_var);
	}
}
