/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:51:44 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/22 21:32:40 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (count);
}

char	**split_with_delimiter(char *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	result = calloc(ft_count_words(s, c) + 3, (sizeof(char *)));
	if (!result)
		return (NULL);
	while (s[j])
	{
		if (s[j] != c)
			j++;
		else
		{
			if (i != j)
			{
				result[k] = ft_substr(s, i, j - i);
				k++;
			}
			i = j;
			j++;
		}
	}
	result[k] = ft_substr(s, i, j - i);
	return (result);
}

int	find_in_env(char *key, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], key, ft_strlen(key)))
			return (i);
		i++;
	}
	return (-1);
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

void	open_and_handle_new_terminal(t_command cmd)
{
	int		idx;
	char	*old;

	idx = find_in_env("SHLVL", cmd.env);
	old = ft_substr(cmd.env[idx], 6, ft_strlen(cmd.env[idx]));
	cmd.env[idx] = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(old) + 1));
	execve("minishell", NULL, cmd.env);
}
