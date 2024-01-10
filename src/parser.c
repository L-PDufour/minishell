/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:47:40 by ldufour           #+#    #+#             */
/*   Updated: 2024/01/09 09:32:28 by ldufour          ###   ########.fr       */
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

t_cmd	*command_redirection(t_list **head, t_cmd *cmd)
{
	t_list	*tmp;

	tmp = *head;
	if (tmp && ((t_token *)(tmp)->content)->type == REDIR_IN_T)
	{
		tmp = tmp->next;
		if (tmp && ((t_token *)(tmp)->content)->type == ALPHA_T)
		{
			cmd->infile = ft_strdup(((t_token *)(tmp)->content)->value);
			*head = tmp;
			if (tmp)
				*head = tmp->next;
		}
	}	
  if (tmp && ((t_token *)(tmp)->content)->type == REDIR_OUT_T)
	{
		tmp = tmp->next;
		if (tmp && ((t_token *)(tmp)->content)->type == ALPHA_T)
		{
      cmd->amend = false;
      if (cmd->outfile)
        free(cmd->outfile);
			cmd->outfile = ft_strdup(((t_token *)(tmp)->content)->value);
			*head = tmp;
			if (tmp)
				*head = tmp->next;
		}
	}
	if (tmp && ((t_token *)(tmp)->content)->type == REDIR_AP_T)
	{
		tmp = tmp->next;
		if (tmp && ((t_token *)(tmp)->content)->type == ALPHA_T)
		{
      cmd->amend = true;
			cmd->outfile = ft_strdup(((t_token *)(tmp)->content)->value);
			*head = tmp;
			if (tmp)
				*head = tmp->next;
		}
	}return (cmd);
}

t_cmd	*cmd_creation(t_list **head)
{
	t_cmd	*cmd;
	t_token	*currentToken;

	if (*head == NULL || (*head)->content == NULL)
	{
		return (cmd);
	}
	cmd = safe_calloc(1, sizeof(t_cmd));
	currentToken = (t_token *)(*head)->content;
	if (currentToken->type == PIPE_T)
		return (cmd);
	else if (currentToken->type == ALPHA_T)
	{
		command_table(head, cmd);
	}
	else if (currentToken->type == REDIR_IN_T ||
				currentToken->type == REDIR_OUT_T ||
				currentToken->type == HERE_DOC_T ||
				currentToken->type == REDIR_AP_T)
	{
		command_redirection(head, cmd);
	}
	if (*head)
		*head = (*head)->next;
	return (cmd_creation(head));
}

t_list	*parser(t_list *cmd_list, const t_list *token_list)
{
	t_list	*cmd_node;
	t_cmd	*cmd;
	t_list	*tmp_token;
	t_token	*currentToken;

	log_printf("\n%s\n", "Parser : ");
	tmp_token = (t_list *)token_list;
	while (tmp_token)
	{
		cmd = safe_calloc(1, sizeof(t_cmd));
		while (tmp_token)
		{
			currentToken = (t_token *)tmp_token->content;
			if (currentToken->type == PIPE_T)
			{
				tmp_token = tmp_token->next;
				break ;
			}
			if (currentToken->type == ALPHA_T)
			{
				command_table(&tmp_token, cmd);
			}
			if (currentToken->type == REDIR_IN_T ||
				currentToken->type == REDIR_OUT_T ||
				currentToken->type == HERE_DOC_T ||
				currentToken->type == REDIR_AP_T)
			{
				command_redirection(&tmp_token, cmd);
			}
			// tmp_token = tmp_token->next;
		}
		if (cmd)
		{
			cmd_node = ft_lstnew(cmd);
			ft_lstadd_back(&cmd_list, cmd_node);
			// Move to the next token only if a command was successfully created
			// tmp_token = tmp_token->next;
		}
	}
	return (cmd_list);
}
