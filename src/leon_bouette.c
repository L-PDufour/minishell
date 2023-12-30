/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leon_bouette.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:44:44 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/29 16:49:59 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

char	**envp_path_creation_leon(char **envp)
{
	char	*str;
	int		i;
	char	*temp;
	char	**envp_path;

	str = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
		{
			str = ft_substr(*envp, 5, ft_strlen(*envp));
			envp_path = ft_split(str, ':');
			free(str);
			i = -1;
			while (envp_path[++i] != NULL)
			{
				temp = ft_strjoin(envp_path[i], "/");
				if (temp)
				{
					free(envp_path[i]);
					envp_path[i] = temp;
				}
			}
		}
		envp++;
	}
	return (envp_path);
}

void	exec_leon(t_list *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list->content;
	if (cmd && cmd->cmd_table)
	{
		log_printf("Executing: %s\n", cmd->cmd_table[0]);
		execve(cmd->cmd_table[0], cmd->cmd_table, NULL);
		perror("execve");
	}
}

void	exec_leon(t_list *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list->content;
	if (cmd && cmd->cmd_table)
	{
		log_printf("Executing: %s\n", cmd->cmd_table[0]);
		execve(cmd->cmd_table[0], cmd->cmd_table, NULL);
		perror("execve");
	}
}
void	update_cmd_list(t_list *cmd_list, char **envp)
{
	char	**envp_path;
	t_cmd	*cmd;
	int		i;

	envp_path = envp_path_creation_leon(envp);
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		if (cmd && cmd->cmd_table)
		{
			if (path_verification(envp_path, cmd) == 0)
			{
			}
			else
			{
				printf("Command not found: %s\n", cmd->cmd_table[0]);
			}
		}
		cmd_list = cmd_list->next;
	}
	i = 0;
	while (envp_path[i] != NULL)
	{
		free(envp_path[i]);
		i++;
	}
	free(envp_path);
}

int	**pipes_creation(int lst_size)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = (int **)safe_calloc(lst_size + 1, sizeof(int *));
	while (i < lst_size)
	{
		pipes[i] = (int *)safe_calloc(2, sizeof(int));
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	pipes[i] = NULL;
	return (pipes);
}

void	close_pipes(int lst_size, int **pipes)
{
	int	j;

	j = 0;
	while (j < lst_size)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}
void	process_exec(int i, int lst_size, int **pipes, t_list *cmd_list)
{
	if (lst_size == 1)
		exec_leon(cmd_list);
	if (i == 0)
	{
		dup2(pipes[0][1], STDOUT_FILENO);
		close_pipes(lst_size - 1, pipes);
	}
	else if (i == lst_size - 1)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close_pipes(lst_size - 1, pipes);
	}
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
		close_pipes(lst_size - 1, pipes);
	}
	exec_leon(cmd_list);
	exit(EXIT_SUCCESS);
}

void	free_array(void **content)
{
	int	i;

	i = 0;
	while (content[i] != NULL)
	{
		free(content[i]);
		i++;
	}
	free(content);
}

void	process_fork(t_list *cmd_list, int lst_size)
{
	pid_t	*pid;
	int		i;
	int		status;
	int		**pipes;

	pid = (pid_t *)safe_calloc(lst_size, sizeof(pid_t));
	pipes = pipes_creation(lst_size);
	i = -1;
	while (++i < lst_size && cmd_list)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid[i] == 0)
			process_exec(i, lst_size, pipes, cmd_list);
		else
			cmd_list = cmd_list->next;
	}
	close_pipes(lst_size - 1, pipes);
	i = -1;
	while (++i < lst_size)
		waitpid(pid[i], &status, 0);
	free(pid);
	free_array((void **)pipes);
}
