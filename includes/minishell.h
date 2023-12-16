/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:18:40 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/16 14:38:05 by ldufour          ###   ########.fr       */
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
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// Characters
# define PIPE 124        // |
# define REDIR_I 60      // <
# define REDIR_O 62      // >
# define SINGLE_QUOTE 39 // '
# define DOUBLE_QUOTE 34 // "

// Couleurs
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

// Structures and tokens
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
	int			len;
}				t_token;

typedef struct s_cmd
{
	char		**cmd_table;
	int			expandable;
	int			fd_input;
	int			fd_output;
	char		*outfile;
	char		*infile;
	int			pipe[2];
}				t_cmd;

typedef struct s_command
{
	char		*name;
	char		*option;
	char		*option2;
	char		*cmd_str;
	char		**env_copy;
	char		*old_pwd;
	char		*pwd;
}				t_command;
// Lexer.c
t_list			*tokenizer(const char *str, t_list *token_list);
// Parser.c
t_list			*parser(t_list *cmd_list, const t_list *token_list);
// Utils.c
char	**split_with_delimiter(char *s, char c);
void			update_env(t_command *cmd, char **envp);
char			**copy_env(char **envp, t_command *cmd);
void			*safe_calloc(size_t nmemb, size_t size);
void			clean_table(char **tab);
void			print_in_color(char *color, char *msg);
// Prompt.c
void			exec_cmd(t_command cmd, char **envp);
// cd.c
void			change_dir(char *str, t_command *cmd);
char			*parse_env(char *str);
// Debug.c
void			log_printf(const char *format, ...);
void			print_token_list(t_list *head);
void	print_cmd_list(t_list *head);
// Pwd.c
char			*get_pwd(void);
void exec_pwd(char *cmd);

#endif
