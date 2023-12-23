/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:47:40 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/22 20:31:09 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*command_table(t_list **head, t_cmd *cmd)
{
	int		array_size;
	int		i;
	t_list	*tmp;

	tmp = *head;
	array_size = 1;
	i = 0;
	while (tmp && ((t_token *)tmp->content)->type == ALPHA_T)
	{
		array_size++;
		tmp = tmp->next;
	}
	cmd->cmd_table = safe_calloc(array_size, sizeof(char *));
	tmp = *head; // Reset tmp to the beginning of the command
	while (tmp && ((t_token *)tmp->content)->type == ALPHA_T)
	{
		cmd->cmd_table[i] = ft_strdup(((t_token *)tmp->content)->value);
		i++;
		tmp = tmp->next;
	}
	cmd->cmd_table[i] = NULL; // Null-terminate the cmd_table array
	*head = tmp;
	// Update head to point to the next position after the command
	return (cmd);
}

t_cmd	*cmd_creation(t_list *head)
{
	t_cmd	*cmd;

	cmd = safe_calloc(1, sizeof(t_cmd));
	while (head && head->content)
	{
		printf("Processing token type: %d\n", ((t_token *)head->content)->type);
		if (((t_token *)head->content)->type == PIPE_T)
		{
			head = head->next;
			break ;
		}
		if (((t_token *)head->content)->type == ALPHA_T)
		{
			if (head->previous
				&& ((t_token *)head->previous->content)->type == REDIR_IN_T)
			{
				printf("infile\n");
				printf("Current token value: %s\n",
						((t_token *)head->content)->value);
			}
		}
		head = head->next;
	}
	if (head)
	{
		head = head->next;
	}
	return (cmd);
}

t_list	*parser(t_list *cmd_list, const t_list *token_list)
{
	t_list	*cmd_node;
	t_cmd	*cmd;
	t_list	**tmp_token;

	log_printf("\n%s\n", "Parser : ");
	tmp_token = (t_list **)&token_list;
	while (*tmp_token)
	{
		cmd_node = ft_lstnew((t_cmd *)cmd_creation(*tmp_token));
		if (cmd_node)
			ft_lstadd_back(&cmd_list, cmd_node);
		*tmp_token = (*tmp_token)->next;
	}
	return (cmd_list);
}

void	check_syntax_error(const t_list *tmp, int identifier)
{
	if (identifier == REDIR_I)
	{
		if (tmp->next && ((t_token *)tmp->next->content)->type != ALPHA_T)
		{
			log_printf("syntax error");
		}
	}
	else if (identifier == PIPE)
	{
		if (!tmp->next || !tmp->previous ||
			((t_token *)tmp->next->content)->type != ALPHA_T ||
			((t_token *)tmp->previous->content)->type != ALPHA_T)
		{
			log_printf("syntax error: missing token around |");
		}
	}
}
