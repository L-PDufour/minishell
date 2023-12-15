/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:47:40 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/21 19:07:15 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	{
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
	}
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

void	check_syntax_error(const t_list *tmp, int identifier)
{
	if (identifier == REDIR_I)
	{
		if (tmp->next && ((t_token *)tmp->next->content)->type != ALPHA_T)
		{
			log_printf("syntax error: %c",
						(int)((t_token *)tmp->next->content)->type);
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
// TODO: Error handling when syntax error
// Function for syntax error
void	token_parser(const t_list *token_list)
{
	const t_list	*tmp;
	t_tokentype		current_type;

	tmp = token_list;
	while (tmp)
	{
		if (tmp->content)
		{
			current_type = ((t_token *)tmp->content)->type;
			if (current_type == REDIR_IN_T || current_type == REDIR_OUT_T ||
				current_type == REDIR_AP_T || current_type == HERE_DOC_T)
			{
				check_syntax_error(tmp, REDIR_I);
			}
			else if (current_type == PIPE_T)
			{
				check_syntax_error(tmp, PIPE);
			}
		}
		tmp = tmp->next;
	}
}

t_list	*parser(t_list *cmd_list, const t_list *token_list)
{
	t_list			*cmd_node;
	t_cmd			*cmd;
	static t_list	*tmp;

	log_printf("%s\n", "Parser : ");
	token_parser(token_list);
	tmp = (t_list *)token_list;
	while (tmp)
	{
		cmd_node = ft_lstnew((t_cmd *)cmd_creation(&tmp));
		if (cmd_node)
		{
			ft_lstadd_back(&cmd_list, cmd_node);
			// free(cmd_node);
		}
		// tmp = tmp->next;
	}
	return (cmd_list);
}

char	*parse_env(char *str)
{
	char	**tmp;
	char	*result;
	int		i;
	char	*env_value;
	int		idx;

	idx = 0;
	result = "";
	tmp = split_with_delimiter(str, '$');
	if (!tmp)
		return (str);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i][0] != '$')
			result = ft_strjoin(result, tmp[i]);
		else
		{
			if (ft_strlen(tmp[i]) == 1)
				result = ft_strjoin(result, tmp[i]);
			else
			{
				env_value = getenv(ft_substr(tmp[i], 1, ft_strlen(tmp[i])));
				if (env_value)
					result = ft_strjoin(result, env_value);
			}
		}
		i++;
	}
	clean_table(tmp);
	return (result);
}
