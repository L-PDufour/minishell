/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:39:16 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/15 14:29:10 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_dir(char *str, t_command *cmd)
{
	char	*home;
	char	*current_pwd;
	char	*tmp;

	tmp = cmd->env[find_in_env("OLDPWD", cmd->env)];
	current_pwd = get_pwd();
	home = getenv("HOME");
	if (!str || !strcmp(str, "") || !strcmp(str, "~"))
		str = home;
	else if (!strcmp(str, "-"))
		str = ft_substr(tmp, 7, ft_strlen(tmp));
	else
	{
		str = parse_env(str);
		if (!str || !strcmp(str, ""))
			str = home;
	}
	if (access(str, F_OK))
	{
		print_in_color(RED, "🚨cd: no such file or directory: ");
		print_in_color(RED, str);
		printf("\n");
		return ;
	}
	if (access(str, R_OK))
	{
		print_in_color(RED, "🚨cd: Permission denied\n");
		return ;
	}
	if (!str || !strcmp(str, " ") || chdir(str) != 0)
	{
		print_in_color(RED, "🚨cd: no such file or directory: ");
		print_in_color(RED, str);
		printf("\n");
	}
	else
	{
		cmd->env[find_in_env("PWD", cmd->env)] = ft_strjoin("PWD=", get_pwd());
		cmd->env[find_in_env("OLDPWD", cmd->env)] = ft_strjoin("OLDPWD=",
				current_pwd);
	}
}

char	*parse_env(char *str)
{
	char	**tmp;
	char	*result;
	int		i;
	char	*env_value;
	int		idx;

	idx = 0;
	result = "";
	tmp = split_with_delimiter(str, '$');
	if (!tmp)
		return (str);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i][0] != '$')
			result = ft_strjoin(result, tmp[i]);
		else
		{
			if (ft_strlen(tmp[i]) == 1)
				result = ft_strjoin(result, tmp[i]);
			else
			{
				env_value = getenv(ft_substr(tmp[i], 1, ft_strlen(tmp[i])));
				if (env_value)
					result = ft_strjoin(result, env_value);
			}
		}
		i++;
	}
	clean_table(tmp);
	return (result);
}


//