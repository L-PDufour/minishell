/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:47:40 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/30 14:39:42 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*command_table(t_list **head, t_cmd *cmd)
{
	int		array_size;
	int		i;
	t_list	*tmp;

	tmp = *head;
	array_size = 0;
	i = 0;
	while (tmp && ((t_token *)tmp->content)->type == ALPHA_T)
	{
		array_size++;
		tmp = tmp->next;
	}
	cmd->cmd_table = (char **)safe_calloc(array_size + 1, sizeof(char *));
	tmp = *head;
	while (tmp && ((t_token *)tmp->content)->type == ALPHA_T)
	{
		cmd->cmd_table[i] = ft_strdup(((t_token *)tmp->content)->value);
		i++;
		tmp = tmp->next;
	}
	cmd->cmd_table[i] = NULL;
	*head = tmp;
	return (cmd);
}

t_cmd	*cmd_creation(t_list **head)
{
	t_cmd	*cmd;

	cmd = safe_calloc(1, sizeof(t_cmd));
	if (((t_token *)(*head)->content)->type == PIPE_T)
		*head = (*head)->next;
	if (((t_token *)(*head)->content)->type == ALPHA_T)
	{
		cmd = command_table(head, cmd);
		if (*head)
			*head = (*head)->next;
	}
	return (cmd);
}

t_list	*parser(t_list *cmd_list, const t_list *token_list)
{
	t_list	*cmd_node;
	t_cmd	*cmd;
	t_list	*tmp_token;

	log_printf("\n%s\n", "Parser : ");
	tmp_token = (t_list *)token_list;
	while (tmp_token)
	{
		cmd_node = ft_lstnew((t_cmd *)cmd_creation(&tmp_token));
		if (cmd_node)
			ft_lstadd_back(&cmd_list, cmd_node);
	}
	return (cmd_list);
}
