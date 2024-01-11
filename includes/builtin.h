/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:43:37 by yothmani          #+#    #+#             */
/*   Updated: 2024/01/11 16:37:48 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "../lib/libft/includes/libft.h"
# include "minishell.h"
# include <signal.h>
// #include <curses.h>
// #include <term.h>

typedef struct s_command
{
	char	*name;
	char	*option;
	char	*option2;
	char	*cmd_str;
	char	**env_copy;
	char	**env;
	char	**builtin;
	char	*old_pwd;
	char	*pwd;
	int		exit_status;
	pid_t	pid;
}			t_command;

void		exec_exit(t_command *cmd);
void		parse_cmd(char *str_cmd, t_command *cmd);
void		change_dir(char *str, t_command *cmd);
char		*get_pwd(void);
char		**split_with_delimiter(char *s, char c);
void		open_and_handle_new_terminal(t_command cmd);
int			find_in_env(char *key, char **envp);
void		handle_exit_status(t_command cmd);
#endif
