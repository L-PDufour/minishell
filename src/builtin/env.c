/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:51:44 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/22 21:33:14 by ldufour          ###   ########.fr       */
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

int	exec_env(t_command cmd)
{
	int	i;

	i = 0;
	while (cmd.env[i])
	{
		printf("%s\n", cmd.env[i]);
		i++;
	}
	return (0);
}
