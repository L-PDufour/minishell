/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:59:55 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/21 15:39:59 by yothmani         ###   ########.fr       */
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

void	print_in_color(char *color, char *msg)
{
	printf("\033[%sm%s\033[0m", color, msg);
}

void	*safe_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	ret = ft_calloc(nmemb, size);
	if (!ret)
		exit_prg_at_error("Malloc failure");
	return (ret);
}
