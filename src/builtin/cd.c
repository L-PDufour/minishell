/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:39:16 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/20 10:35:28 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_dir(char *str, t_command *cmd)
{
	char	*home;
	char	**envp;

	home = getenv("HOME");
	if (!str || !strcmp(str, "") || !strcmp(str, "~"))
		str = home;
	else if (!strcmp(str, "-"))
		str = getenv("OLDPWD");
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
		update_env(cmd, envp);
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
	// renconstruire tmp (2eme validation du contenu du tableau tmp)
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
	free(str);
	return (result);
}
// TODO: free str si progbleme

char	*parse_env_token(char *str)
{
	char	**tmp;
	char	*result;
	int		i;
	char	*env_value;
	char	*new_result;

	result = ft_strdup(""); // Initialize result with an empty string
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
				{
					new_result = ft_strjoin(result, env_value);
					free(result); // Free the previous result
					result = new_result;
				}
			}
		}
		i++;
	}
	clean_table(tmp);
	free(str);
	return (result);
}
