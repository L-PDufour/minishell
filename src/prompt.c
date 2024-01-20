/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:45:53 by yothmani          #+#    #+#             */
/*   Updated: 2024/01/20 16:53:30 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*print_colored_message(const char *user, const char *path)
{
	char	*message;

	message = (char *)malloc(1024);
	if (message == NULL)
		return (NULL);
	ft_strcpy(message, "\033[1;33m┌─[\033[1;33m");
	ft_strcat(message, user);
	ft_strcat(message, "\033[1;33m]- \033[1;32m");
	ft_strcat(message, path);
	ft_strcat(message, " \n│\n└──────────> \033[1;34m🔥Ready... 🔥 \033[0m");
	return (message);
}

char	*display_prompt(void)
{
	char	*path;
	char	*read_cmd;
	char	*msg;
  // HACK: Laisser en commentaire. Cause des leaks  
	// path = get_pwd();
	// msg = print_colored_message(getenv("USER"), path);
	read_cmd = readline("minishell>: ");
	return (read_cmd);
}
