/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:59:55 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/14 01:39:49 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_white_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

char	*trim_str(char *str)
{
	int		i;
	int		j;
	bool	is_space;
	char	*trimmed_str;

	i = 0;
	j = 0;
	is_space = false;
	while (is_white_space(str[i]))
		i++;
	trimmed_str = calloc(sizeof(char), strlen(str) - i + 1);
	while (str[i])
	{
		if (is_white_space(str[i]))
			is_space = true;
		if (!is_white_space(str[i]))
		{
			if (is_space)
			{
				trimmed_str[j++] = ' ';
				is_space = false;
			}
			trimmed_str[j++] = str[i];
		}
		i++;
	}
	str = NULL;
	return (trimmed_str);
}

void	clean_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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

void	print_in_color(char *color, char *msg)
{
	printf("\033[%sm%s\033[0m", color, msg);
}

void	exit_prg_at_error(char *str)
{
	printf("Error\n");
	if (str)
		printf("%s\n", str);
	exit(EXIT_FAILURE);
}
void	*safe_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	ret = ft_calloc(nmemb, size);
	if (!ret)
		exit_prg_at_error("Malloc failure");
	return (ret);
}

void	init_env(t_command *cmd)
{
	cmd->pwd = NULL;
	cmd->old_pwd = NULL;
}

void	update_env(t_command *cmd, char **envp)
{
	int	i;

	
	i = 0;
	cmd->env_copy = envp;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PWD=", 4))
			cmd->old_pwd = ft_substr(envp[i], 4, ft_strlen(envp[i]));
		i++;
	}
	cmd->pwd = get_pwd();
}
char	**copy_env(char **envp, t_command *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (envp[count])
		count++;
	cmd->env_copy = malloc(sizeof(char *) * count + 1);
	if (!cmd->env_copy)
		return (NULL);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PWD=", 4))
			cmd->env_copy[i] = ft_strjoin("PWD=", get_pwd());
		else if (ft_strnstr(envp[i], "OLDPWD=", 7))
			cmd->env_copy[i] = ft_strjoin("OLDPWD=", strdup(cmd->old_pwd));
		else
			cmd->env_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	cmd->env_copy[i] = NULL;
	return (cmd->env_copy);
}
