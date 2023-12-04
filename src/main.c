/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/04 17:01:50 by ldufour          ###   ########.fr       */
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
			cmd_table = ft_split(cmd_line, ' ');
			// get token
			// scan token
			// next token
			Pid = fork();
			if (childPid == 0)
			{
				// execve("/usr/bin/df", , envp);
			}
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
