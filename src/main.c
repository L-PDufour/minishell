/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2023/11/30 13:04:21 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
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
int	main(int argc, char **argv)
{
	int pipe[2];

	argc = 0;
	// https://www.cs.cornell.edu/courses/cs414/2004su/homework/shell/shell.html
	while (1)
	{
		int childPid;
		char *cmdline;
		printf("test>");
		cmdline = readline("");
		cmdline = *parsing_arguments(*argv);
		if (cmdline)
		{
		childPid = fork();
			if (childPid == 0)
			{

			}
		}
	}
}

