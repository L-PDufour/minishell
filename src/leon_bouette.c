
#include "../includes/minishell.h"

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

	cmd = (t_cmd *)cmd_list->content;
	if (cmd && cmd->cmd_table)
	{
		execve(cmd->cmd_table[0], cmd->cmd_table, NULL);
		perror("execve");
	}
}

int	path_verification(char **envp_path, t_cmd *cmd)
{
	int		i;
	char	*str;

	i = 0;
	while (envp_path[i] != NULL)
	{
		str = ft_strjoin(envp_path[i], cmd->cmd_table[0]);
		if (access(str, F_OK | X_OK) == 0)
		{
			cmd->cmd_table[0] = ft_strdup(str);
			free(str);
			return (0);
		}
		free(str);
		i++;
	}
	return (1);
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
