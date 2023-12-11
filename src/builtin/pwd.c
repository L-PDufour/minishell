/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:56:45 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/09 23:36:47 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_pwd()
{
    char *path;

    path = getcwd(NULL, 0);
    return(path);
}

void exec_pwd(char *cmd)
{
    if(!strcmp(cmd, ""))
		    printf("%s\n", get_pwd());
        else
            print_in_color(RED, "🚨pwd: too many arguments\n");
}
