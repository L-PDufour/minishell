/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/11 14:58:03 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_prg_at_error(char *str)
{
	printf("Error\n");
	if (str)
		printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	*safe_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	ret = ft_calloc(nmemb, size);
	if (!ret)
		exit_prg_at_error("Malloc failure");
	return (ret);
}

void	getToken(char *str, int i, t_list *head)
{
}
// TODO Je passe ma cmd, je la remplis et apres je la rajoute a ma linked list
// Dois penser a proteger si NULL pour ne pas derefencer un pointer NULL
void	recursive_tokenizer(char *str, int i, t_list **head)
{
	t_cmd	*cmd;
	t_list	*node;

	if (!str || str[i] == '\0')
		return ;
	node = ft_lstnew(cmd);
	getToken(str, i, *head);
	ft_lstadd_front(head, (void *)cmd);
	recursive_tokenizer(str, i, head);
	return ;
}

// TODO Je crois que cette fonction sert à rien
t_list	**init_struct(void)
{
	static t_list	**head;

	// static t_cmd	*command;
	// command = safe_calloc(1, sizeof(t_cmd));
	head = safe_calloc(1, sizeof(t_list *));
	// head = ft_lstnew(command);
	return (head);
}

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd;
	char		*cmd_str;

	(void)argc;
	(void)argv;
	while (true)
	{
		cmd_str = display_prompt();
		cmd_str = trim_str(cmd_str);
		if (strcmp(cmd_str, ""))
		{
			parse_cmd(cmd_str, &cmd);
			// printf("name: %s\n", cmd.name);
			// printf("opt: %s\n", cmd.option);
			// printf("opt2: %s\n", cmd.option2);
			exec_cmd(cmd, envp);
		}
	}
	free(cmd_str);
	return (0);
}

// Pseudo code
// cmd_line = readline
// while cmd_line
// malloc struct node
// struct.type = getToken(cmd_line)
// getGrammar(struct, cmd_line)
// cmd_line++
