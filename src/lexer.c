/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:37:22 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/21 15:37:57 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO: Condenser le code et faire des sous-fonctions
static int	meta_token(const char *str, int i, t_token *token)
{
	if (str[i] == '\0')
		return (i);
	else if (str[i] == PIPE)
		token->type = PIPE_T;
	else if (str[i] == REDIR_I)
	{
		token->type = REDIR_IN_T;
		if (str[i + 1] == REDIR_I)
		{
			token->type = HERE_DOC_T;
			i++;
		}
	}
	else if (str[i] == REDIR_O)
	{
		token->type = REDIR_OUT_T;
		if (str[i + 1] == REDIR_O)
		{
			token->type = REDIR_AP_T;
			i++;
		}
	}
	return (i++);
}

// TODO: mettre len t_token et gerer les quotes si quotes mettre l'env
// necessaire tout de suite
static int	getToken(const char *str, int i, t_token *token)
{
	int	j;

	if (str[i] == '\0')
		return (i);
	else if (ft_strchr("<>|", str[i]))
		i = meta_token(str, i, token);
	else if (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE)
		i = quotes_parser(str, i, token, str[i]);
	else if (!ft_strchr("<>|", str[i]))
	{
		j = i;
		while (str[i] != '\0' && !is_white_space(str[i]) &&
				!ft_strchr("<>|", str[i]))
		{
			i++;
		}
		token->value = parse_env(ft_substr(str, j, i - j));
		token->type = ALPHA_T;
		token->len = i - j;
	}
	return (i++);
}

t_list	*tokenizer(const char *str, t_list *token_list)
{
	int		i;
	int		len;
	t_token	*token;

	i = 0;
	len = ft_strlen(str);
	token = NULL;
	while (i < len)
	{
		token = safe_calloc(1, sizeof(t_token));
		if (str[i] <= 32) // TODO: whitespace
			i++;
		i = getToken(str, i, token);
		if (token)
		{
			ft_lstadd_back(&token_list, ft_lstnew((t_token *)token));
		}
		i++;
	}
	log_printf("tokenizer : \n"); // HACK: DEBUG
	return (token_list);
}
//TODO:
//Test the double quotes' function