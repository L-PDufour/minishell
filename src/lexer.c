/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:37:22 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/15 16:48:44 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_iswhitespace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

// TODO: not working
// Je dois traiter les quotes en pair peu importe "'"USER"'" est egal a ' USER '
static int	quotes_parser(const char *str, int i, t_token *token, int delimiter)
{
	int	j;
	delimiter == DOUBLE_QUOTE;
	i++;
	j = i;
	while (str[i])
	{
		if(str[i] == delimiter)
			break;
		i++;
	}
		// increment until delimiter is found
		// extract the string  
		// parse_env;
		// log_printf("the expandables");
	if (str[i] != DOUBLE_QUOTE)
	{
		print_in_color(RED, "🚨Error: Double quote opened but not closed\n");
		return(-1);
	}
	token->type = ALPHA_T;
	token->value = parse_env(ft_substr(str, j, ((i - 1) - j)));
	token->len = i - j;
	return (i);
}

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
		while (str[i] != '\0' && !ft_iswhitespace(str[i]) &&
				!ft_strchr("<>|", str[i]))
		{
			if (str[i] == '$') // TODO: EXPANDER
				log_printf("the expandables");
			i++;
		}
		token->value = ft_substr(str, j, i - j);
		token->type = ALPHA_T;
		token->len = i - j;
	}
	return (i++);
}

// TODO: Je passe ma cmd, Boucle a tester
t_list	*tokenizer(const char *str, t_list *token_list)
{
	int		i;
	t_list	*tok_node;
	t_token	*token;
	int		len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		token = safe_calloc(1, sizeof(t_token));
		if (str[i] <= 32)
			i++;
		i = getToken(str, i, token);
		if (token)
		{
			tok_node = ft_lstnew((t_token *)token);
			ft_lstadd_back(&token_list, tok_node);
		}
		i++;
	}
	// HACK: TO TEST LINKED LIST
	log_printf("tokenizer : ");
	print_token_list(token_list);
	log_printf("\n");
	return (token_list);
}
    //TODO:
	//Test the double quotes' function 