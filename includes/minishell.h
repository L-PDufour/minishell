/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:18:40 by yothmani          #+#    #+#             */
/*   Updated: 2024/01/20 16:57:08 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/includes/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

/*#############################|| Characters ||#####################*/
# define PIPE 124        // |
# define REDIR_I 60      // <
# define REDIR_O 62      // >
# define SINGLE_QUOTE 39 // '
# define DOUBLE_QUOTE 34 // "

/*#############################|| Colors ||#####################*/
# define RED "1;31"
# define GREEN "1;32"
# define YELLOW "1;33"
# define BLUE "1;34"
# define MAGENTA "1;35"
# define CYAN "1;36"
# define WHITE "1;37"
# define BOLD_RED "1;91"
# define BOLD_GREEN "1;92"
# define BOLD_YELLOW "1;93"
# define BOLD_BLUE "1;94"
# define BOLD_MAGENTA "1;95"
# define BOLD_CYAN "1;96"
# define BOLD_WHITE "1;97"

/*#############|| Structures and tokens ||################*/
typedef enum e_tokentype
{
	ALPHA_T = 97,
	REDIR_IN_T = 60,
	REDIR_OUT_T = 62,
	REDIR_AP_T = 43,
	PIPE_T = 124,
	HERE_DOC_T = 45,
}				t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*value;
	bool		append;
}				t_token;

typedef struct s_cmd
{
	char		**cmd_table;
	bool		built_in;
	bool		amend;
	int			fd_input;
	int			fd_output;
	char		*outfile;
	char		*infile;
	char		*name;
	char		*option;
	char		*option2;
	char		**env;
	char		*cmd_str;
	char		**env_copy;
	char		**builtin;
	char		*old_pwd;
	char		*pwd;
	int			exit_status;
	char		*export_value;
	char		*export_key;
	pid_t		pid;
}				t_cmd;

/*#############################|| lexer.c ||##############################*/
t_list			*tokenizer(const char *str, t_list *token_list);
void			temp_error(int i, t_list *token_list, t_token *token);
int				quotes_parser(const char *str, int i, t_token *token,
					int delimiter);

/*#############################|| lexer.c ||##############################*/
char			*parse_env(char *str);
char			*parse_env2(t_cmd cmd, char *str);
void			token_parser(const t_list *token_list);
t_list			*parser(t_list *cmd_list, const t_list *token_list);
void			lexer_error(int c, t_list *head, void (*del)(void *));
// TODO: Leon bouette
void			exec_leon(t_list *cmd_list);
void			update_cmd_list(t_list *cmd_list, char **envp);
void			process_fork(t_list *cmd_list, int lst_size);

/*#############################|| utils.c ||##############################*/
char			*trim_str(char *str);
void			*safe_calloc(size_t nmemb, size_t size);
void			print_in_color(char *color, char *msg);
bool			is_white_space(char c);
int				ft_strcmp(char *s1, char *s2);
void			close_pipes(int lst_size, int **pipes);
/*#############################|| debug.c ||##############################*/
void			log_printf(const char *format, ...);
void			print_cmd(void *content);
void			print_token(void *content);

/*#############################|| Prompt.c ||############################*/
char			*display_prompt(void);
static char		*print_colored_message(const char *user, const char *path);

/*#############################|| free_and_exit.c ||#####################*/

void			exit_prg_at_error(char *str);
void			free_token(void *token_ptr);
void			free_cmd(void *cmd);
void			clean_table(char **table);
void			free_array(void **content);

int				**pipes_creation(int lst_size);
void			main_exec(t_list *cmd_list, char **envp);
void			clean_process(t_list *token_list, t_list *cmd_list,
					char *cmd_str);

/*#############################|| signals.c ||#####################*/

void			init_signal_handlers(void);

/*#############################|| builtin.c ||#####################*/
void			exec_cmd(t_cmd cmd, char **envp);
int				exec_builtin(t_cmd *cmd, char **envp);
void			exec_pwd(t_cmd *cmd);
void			exec_env(t_cmd *cmd);
void			exec_echo(t_cmd cmd);
// void	exec_non_builtin(t_cmd cmd, char **envp);
void			exec_exit(t_cmd *cmd);
void			parse_cmd(char *str_cmd, t_cmd *cmd);
void			change_dir(char *str, t_cmd *cmd);
char			*get_pwd(void);
char			**split_with_delimiter(char *s, char c);
void			open_and_handle_new_terminal(t_cmd *cmd);
int				find_in_env(char *key, char **envp);
void			handle_exit_status(t_cmd cmd);
void			update_env(t_cmd *cmd, char *new_var);
void			export_exec(t_cmd *cmd);
void			exec_unset(t_cmd *cmd);

#endif
