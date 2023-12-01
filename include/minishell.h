/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:39:58 by ldufour           #+#    #+#             */
/*   Updated: 2023/11/30 11:00:01 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// TODO enum et norminette
// Penser à la gestion des processus
// Travailler sur de quoi qui marche pour ne pas attendre vs diviser le travail
// Commencer par executer une commande
// Developpper l'intelligence ensuite

typedef enum TokenType{

	COMMAND,
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_AMEND,
	PIPE,
	HERE_DOC,

} TokenType;

typedef struct t_cmd{
	char **cmd_table;
	int fd_input;
	int fd_output;
	char *outfile;
	char *infile;
	int pipe[2];
} s_cmd;

#endif
