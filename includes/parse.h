/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:00:23 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/30 13:53:58 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H
#include "minishell.h"

typedef struct s_cmd {
  char **cmd_table;
  int expandable;
  int fd_input;
  int fd_output;
  char *outfile;
  char *infile;
  int pipe[2];
} t_cmd;

char *parse_env(char *str);
void token_parser(const t_list *token_list);
t_list *parser(t_list *cmd_list, const t_list *token_list);
void lexer_error(int c, t_list *head, void (*del)(void *));
// TODO: Leon bouette
char **envp_path_creation_leon(char **envp);
void	exec_leon(t_list *cmd_list);
int path_verification(char **envp_path, t_cmd *cmd); 
void update_cmd_list(t_list *cmd_list, char **envp); 
void	process_fork(t_list *cmd_list, int lst_size);
void	free_array(void **content);
#endif
