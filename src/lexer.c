/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:37:22 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/14 15:36:15 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool ft_iswhitespace(int c) {
  if (c == 32 || (c >= 9 && c <= 13))
    return (true);
  return (false);
}

// TODO: not working
// int	quotes_parser(const char *str, int c, int i)
// {
// 	int	j;
// 	int	k;
//
// 	j = i;
// 	k = i;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == c)
// 		{
// 			j = i + 1;
// 			while (str[j] != '\0' && (!ft_iswhitespace(str[j])
// 					&& !ft_strchr("<>|", str[j])))
// 			{
// 				j++;
// 			}
// 			if (c == '\0')
// 			{
// 				log_printf("quote error\n");
// 				break ;
// 			}
// 		}
// 		i++;
// 	}
// 	log_printf("%s", ft_substr(str, k, j));
// 	return (i);
// }

// TODO: Condenser le code et faire des sous-fonctions
int	ft_isspecial(const char *str, int i, t_token *token)
{
	if (str[i] == '\0')
		return (i);
	else if (str[i] == PIPE)
	{
		token->type = PIPE_T;
		log_printf("PIPE ");
		i++;
	}
	else if (str[i] == REDIR_I)
	{
		token->type = REDIR_IN_T;
		if (str[i + 1] == REDIR_I)
		{
			token->type = HERE_DOC_T;
			i++;
		}
		log_printf("REDIR_I ");
		i++;
	}
	else if (str[i] == REDIR_O)
	{
		token->type = REDIR_OUT_T;
		if (str[i + 1] == REDIR_O)
		{
			token->type = REDIR_AM_T;
			i++;
		}
		log_printf("REDIR_O ");
		i++;
	}
	return (i);
}

// TODO: mettre len t_token et gerer les quotes
int	getToken(const char *str, int i, t_token *token)
{
	int	j;

	if (ft_iswhitespace(str[i]))
		i++;
	if (ft_isalpha(str[i]) || str[i] == '-')
	{
		j = i;
		while (str[i] != '\0' && ft_isalpha(str[i]) || str[i] == '-')
			i++;
		token->value = ft_substr(str, j, i - j);
		token->type = ALPHA_T;
		log_printf("WORD ");
	}
	else if (ft_strchr("<>|", str[i]))
		i = ft_isspecial(str, i, token);
	// TODO: implement quotes_parser
	// else if (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE)
	// i = quotes_parser(str, str[i], i);
	else
		i++;
	return (i);
}

// TODO: Je passe ma cmd,
t_list	*tokenizer(const char *str, t_list *token_list)
{
	static int	i;
	t_list		*tok_node;
	t_token		*token;

	i = 0;
	while (str[i] != '\0')
	{
		token = safe_calloc(1, sizeof(t_token));
		i = getToken(str, i, token);
		if (token)
		{
			tok_node = ft_lstnew((t_token *)token);
			ft_lstadd_back(&token_list, tok_node);
		}
	}
	// HACK: TO TEST LINKED LIST
	// while (token_list)
	// {
	// 	printf("%s\n", ((t_token *)token_list->content)->value);
	// 	token_list = token_list->next;
	// }
	return (token_list);
}
