/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:47:40 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/18 08:38:22 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*command_table(t_list *tmp, t_list **head, t_cmd *cmd)
{
	int	array_size;
	int	i;

	array_size = 1;
	i = 0;
	while (tmp && ((t_token *)tmp->content)->type == ALPHA_T)
	{
		array_size++;
		tmp = tmp->next;
	}
	cmd->cmd_table = safe_calloc(array_size, sizeof(char *));
	while (*head && ((t_token *)(*head)->content)->type == ALPHA_T)
	{
		cmd->cmd_table[i] = ft_strdup(((t_token *)(*head)->content)->value);
		i++;
		*head = (*head)->next;
	}
	cmd->cmd_table[i] = NULL;
	return (cmd);
}

t_cmd	*cmd_creation(t_list **head)
{
	int		i;
	int		array_size;
	t_cmd	*cmd;
	t_list	*tmp;

	tmp = *head;
	i = 0;
	array_size = 1;
	cmd = safe_calloc(1, sizeof(t_cmd));
	if (((t_token *)(*head)->content)->type == PIPE_T)
	{
		*head = (*head)->next;
		tmp = *head;
	}
	if (((t_token *)(*head)->content)->type == ALPHA_T)
		cmd = command_table(tmp, head, cmd);
	// else if (((t_token *)token_list->content)->type == REDIR_IN_T)
	// {
	// 	token_list = token_list->next;
	// 	cmd->infile = ft_strdup(((t_token *)token_list->content)->value);
	// 	token_list = token_list->next;
	// }
	// else if (((t_token *)token_list->content)->type == REDIR_OUT_T
	// 		|| ((t_token *)token_list->content)->type == REDIR_AP_T)
	// {
	// 	token_list = token_list->next;
	// 	cmd->outfile = ft_strdup(((t_token *)token_list->content)->value);
	// 	token_list = token_list->next;
	// }
	return (cmd);
}



t_list	*parser(t_list *cmd_list, const t_list *token_list)
{
	t_list			*cmd_node;
	t_cmd			*cmd;
	static t_list	*tmp;

	log_printf("%s\n", "Parser : ");
	tmp = (t_list *)token_list;
	while (tmp)
	{
		cmd_node = ft_lstnew((t_cmd *)cmd_creation(&tmp));
		if (cmd_node)
			ft_lstadd_back(&cmd_list, cmd_node);
	}
	return (cmd_list);
}
