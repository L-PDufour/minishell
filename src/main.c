/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/06 13:34:30 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <unistd.h>

bool	ft_iswhitespace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

char	**parsing_arguments(char *argv)
{
	char	**argument;
	int		i;

	i = -1;
	argument = NULL;
	while (argv[++i] != '\0')
	{
		if (argv[i] != 32 && ft_iswhitespace(argv[i]) == 1)
			argv[i] = ' ';
	}
	argument = ft_split(argv, ' ');
	return (argument);
}

// void	child_process_1(char **argv, char **envp, t_pipex *pipex)
// {
// 	exit_pipex(dup2(pipex->infile, STDIN_FILENO), "dup2 error", pipex);
// 	exit_pipex(dup2(pipex->fd[1], STDOUT_FILENO), "dup2 error", pipex);
// 	close(pipex->fd[0]);
// 	close(pipex->infile);
// 	pipex->cmd_args = parsing_arguments(argv[2]);
// 	path_verification(pipex);
// 	execve(pipex->cmd_path, pipex->cmd_args, envp);
// 	exit_pipex(-1, "Can't execute child process 1", pipex);
// }
//
// void ft_isspecial(char c)
// {
//     const char *special_chars = "|<>\"'";
//     
//     if (ft_strchr(special_chars, c) != NULL)
//         printf("%c is a special character\n", c);
// }
//
void ft_isspecial(int c)
{
	if (c == PIPE)
		printf("PIPE");
	else if (c == REDIR_I)
		printf("REDIR_I");
	else if (c == REDIR_O)
		printf("REDIR_O");
	else if (c == SPACE)
		printf("SPACE");
	else if (c == TAB)
		printf("TAB");
	else if (c == NEWLINE)
		printf("NEWLINE");
	else if (c == SINGLE_QUOTE)
		printf("SINGLE_QUOTE");
	else if (c == DOUBLE_QUOTE)
		printf("DOUBLE_QUOTE");
	else if (c == BACKSLASH)
		printf("BACKSLASH");
	else if (ft_isalpha(c))
		printf("STRING");
	// Add more conditions for other defines as needed
	// else
		// printf("Not a special character");
}

int	getToken(char *str)
{
	int	i;
	int	type;

	type = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_iswhitespace(str[i])) // avancer la str en cas d'espace
			i++;
		ft_isspecial(str[i]);
		i++;	
	}
	return (type);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe[2];
	int		childPid;
	char	*cmd_line;
	char	**cmd_table;
	pid_t	Pid;

	// argc = 0;
	// https://www.cs.cornell.edu/courses/cs414/2004su/homework/shell/shell.html
	while (1)
	{
		printf("test>");
		cmd_line = readline("");
		// cmd_line = *parsing_arguments(*argv);
		if (cmd_line)
		{
			// add_history(cmd_line);
			getToken(cmd_line);
			// scan token
			// next token
			printf("\n");
			free(cmd_line);
		}
	}
	wait(NULL);
}
// https://www.youtube.com/watch?v=SToUyjAsaFk&list=PLGU1kcPKHMKj5yA0RPb5AK4QAhexmQwrW&index=19
// Regarder pour la creation d'un recursive descent parser
//
// Creer des regles
// cmd_table[0] doit etre une commande
// si < ou > ca foit etre un filename qui suit
