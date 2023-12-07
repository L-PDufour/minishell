/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:39:58 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/07 07:59:09 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/wait.h>

# define PIPE 124        // |
# define REDIR_I 60      // <
# define REDIR_O 62      // >
# define APPEND
# define HEREDOC
// # define SPACE 32        // ' '
// # define TAB 9           // '\t'
// # define NEWLINE 10      // '\n'
# define SINGLE_QUOTE 39 // '
# define DOUBLE_QUOTE 34 // "
# define BACKSLASH 92    // \
# define DOLLAR      36  // $

// TODO enum et norminette
// Penser à la gestion des processus
// Travailler sur de quoi qui marche pour ne pas attendre vs diviser le travail
// Commencer par executer une commande
// Developpper l'intelligence ensuite

// typedef enum TokenType
// {
//
// 	COMMAND,
// 	REDIR_INPUT,
// 	REDIR_OUTPUT,
// 	REDIR_AMEND,
// 	PIPE,
// 	HERE_DOC,
//
// }				TokenType;
//
typedef struct t_cmd
{
	// TokenType	token_type;
	char		**cmd_table;
	int			fd_input;
	int			fd_output;
	char		*outfile;
	char		*infile;
	int			pipe[2];
}				s_cmd;

bool			ft_iswhitespace(int c);

bool	ft_iswhitespace(int c);

#endif
