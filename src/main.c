/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/07 16:45:06 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <malloc/_malloc.h>

// bool	ft_iswhitespace(int c)
// {
// 	if (c == 32 || (c >= 9 && c <= 13))
// 		return (true);
// 	return (false);
// }
//
// char	**parsing_arguments(char *argv)
// {
// 	char	**argument;
// 	int		i;
//
// 	i = -1;
// 	argument = NULL;
// 	while (argv[++i] != '\0')
// 	{
// 		if (argv[i] != 32 && ft_iswhitespace(argv[i]) == 1)
// 			argv[i] = ' ';
// 	}
// 	argument = ft_split(argv, ' ');
// 	return (argument);
// }
//
// // void	child_process_1(char **argv, char **envp, t_pipex *pipex)
// // {
// // 	exit_pipex(dup2(pipex->infile, STDIN_FILENO), "dup2 error", pipex);
// // 	exit_pipex(dup2(pipex->fd[1], STDOUT_FILENO), "dup2 error", pipex);
// // 	close(pipex->fd[0]);
// // 	close(pipex->infile);
// // 	pipex->cmd_args = parsing_arguments(argv[2]);
// // 	path_verification(pipex);
// // 	execve(pipex->cmd_path, pipex->cmd_args, envp);
// // 	exit_pipex(-1, "Can't execute child process 1", pipex);
// // }
// //
// // void ft_isspecial(char c)
// // {
// //     const char *special_chars = "|<>\"'";
// //
// //     if (ft_strchr(special_chars, c) != NULL)
// //         printf("%c is a special character\n", c);
// // }
// //
// TokenType	validate_token(char *str, int c)
// {
// 	if (*str && *str == PIPE && ft_iswhitespace(*(str + 1)))
// 	{
// 		str++;
// 		return (PIPE_T);
// 	}
// 	else if (*str && *str == REDIR_I)
// 	{
// 		if (ft_iswhitespace(*(str + 1)) && str++)
// 		{
// 			return (REDIR_INPUT_T);
// 		}
// 		else if (*(str + 1) == REDIR_I && *(str + 2) == REDIR_I
// 			|| ft_iswhitespace(*(str + 2)))
// 		{
// 			return (HERE_DOC_T);
// 		}
// 	}
// 	return (0);
// }
//
// int	ft_isspecial(char *str, int i, t_cmd *cmd)
// {
// 	int	j;
//
// 	j = i;
// 	if (str[j] == PIPE)
// 		cmd->token_type = validate_token(&str[j], PIPE);
// 	else if (str[j] == REDIR_I)
// 	{
// 		cmd->token_type = validate_token(&str[j], REDIR_I);
// 	}
// 	else if (str[j] == REDIR_O)
// 	{
// 		cmd->token_type = validate_token(&str[j], REDIR_O);
// 		if (str[j + 1] == REDIR_O)
// 		{
// 			printf("APPEND ");
// 			j++;
// 			return (j);
// 		}
// 		else
// 			printf("REDIR_O ");
// 	}
// 	else if (str[j] == SINGLE_QUOTE)
// 		printf("SINGLE_QUOTE ");
// 	else if (str[j] == DOUBLE_QUOTE)
// 		printf("DOUBLE_QUOTE ");
// 	else if (str[j] == '\\')
// 		printf("BACKSLASH ");
// 	else if (ft_isalpha(str[j]))
// 	{
// 		printf("STRING ");
// 		while (ft_isalpha(str[j]))
// 		{
// 			j++;
// 		}
// 		return (j);
// 	}
// 	// Add more conditions for other characters as needed
// 	// else
// 	// printf("Not a special character");
// 	return ();
// }
//

// {
// 	int	i;
// 	int	type;
//
// 	type = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (ft_iswhitespace(str[i])) // avancer la str en cas d'espace
// 			i++;
// 		i = ft_isspecial(str, i);
// 		i++;
// 	}
// 	return (type);
// }
//
// je pourrais iterer à travers ma ligne et à chaque token retourner un type et
// creer une nouvelle node
// ex ls -la
// string
// creer string

int	main(int argc, char **argv, char **envp)
{
	int		pipe[2];
	int		childPid;
	char	*cmd_line;
	char	**cmd_table;
	pid_t	Pid;
	t_cmd	*cmd;
	t_list	*node;

	// argc = 0;
	// https://www.cs.cornell.edu/courses/cs414/2004su/homework/shell/shell.html
	cmd_line = "";
	cmd = malloc(sizeof(t_cmd));
	cmd->fd_input = 1;
	node = ft_lstnew(cmd);
	node->content = (void *)cmd;
	((t_cmd *)node)->fd_input = 1;
	printf("%i\n", ((t_cmd *)node)->fd_input);
	// (t_cmd *)node->content->;
	// while (cmd_line != NULL)
	// {
	//
	// 	printf("test>");
	// 	// cmd_line = readline("");
	// 	cmd_line = "<<< infile > < >>> ||";
	// 	getToken(cmd_line);
	// 	cmd_line = NULL;
	// 	free(cmd_line);
	// 	printf("\n");
	// 	// get token
	// 	// scan token
	// 	// next token
	// 	// Pid = fork();
	// 	// if (childPid == 0)
	// 	// {
	// 	// execve("/usr/bin/df", , envp);
	// 	// }
	// 	// getToken(cmd_line);
	// 	// scan token
	// 	// next token
	// 	// printf("\n");
	// 	// free(cmd_line);
	// }
	return (0);
}
// https://www.youtube.com/watch?v=SToUyjAsaFk&list=PLGU1kcPKHMKj5yA0RPb5AK4QAhexmQwrW&index=19
// Regarder pour la creation d'un recursive descent parser
//
// Creer des regles
// cmd_table[0] doit etre une commande
// si < ou > ca foit etre un filename qui suit
//
// Pseudo code
// cmd_line = readline
// while cmd_line
// malloc struct node
// struct.type = getToken(cmd_line)
// getGrammar(struct, cmd_line)
// cmd_line++
