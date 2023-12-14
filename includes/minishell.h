/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:39:58 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/14 11:03:04 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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

# define PIPE 124   // |
# define REDIR_I 60 // <
# define REDIR_O 62 // >
# define APPEND
# define HEREDOC
// # define SPACE 32        // ' '
// # define TAB 9           // '\t'
// # define NEWLINE 10      // '\n'
# define SINGLE_QUOTE 39 // '
# define DOUBLE_QUOTE 34 // "
/* # define BACKSLASH 92 // \ */
/* # define DOLLAR      36  // $ */

// TODO enum et norminette
// Penser à la gestion des processus
// Travailler sur de quoi qui marche pour ne pas attendre vs diviser le travail
// Commencer par executer une commande
// Developpper l'intelligence ensuite

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

typedef enum e_tokentype
{
	ALPHA_T,
	REDIR_IN_T,
	REDIR_OUT_T,
	REDIR_AM_T,
	PIPE_T,
	HERE_DOC_T,

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
}				t_command;
// Utils

void			*safe_calloc(size_t nmemb, size_t size);

// Lexer.c
int	getToken(const char *str, int i, t_token *token);
t_list	*tokenizer(const char *str, t_list *token_list);
int				quotes_parser(const char *str, int c, int i);
int	ft_isspecial(const char *str, int i, t_token *token);
bool			ft_iswhitespace(int c);

void			print_in_color(char *color, char *msg);
void			exec_cmd(t_command cmd, char **envp);
char			*display_prompt(void);
char			*get_pwd(void);
void			parse_cmd(char *str_cmd, t_command *cmd);
bool			is_white_space(char c);
char			*trim_str(char *str);
void			change_dir(char *str);
char			*parse_env(char *str);
void			exec_pwd(char *cmd);
void			clean_table(char **tab);
char			**split_with_delimiter(char *s, char c);
// Debug.c
void			log_printf(const char *format, ...);
const char *token_type_to_str(t_tokentype type);
void print_token_list(t_list *head);

#endif
