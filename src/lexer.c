/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:37:22 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/13 14:10:49 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO: need more testing
int	quotes_parser(char *str, int c, int i)
{
	int	j;
	int	k;

	j = i;
	k = i;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			j = i + 1;
			while (str[j] != '\0' && (!ft_iswhitespace(str[j])
					&& !ft_strchr("<>|", str[j])))
			{
				j++;
			}
			if (c == '\0')
			{
				log_printf("quote error\n");
				break ;
			}
		}
		i++;
	}
	log_printf("%s", ft_substr(str, k, j));
	return (i);
}

int	ft_isspecial(char *str, int i)
{
	if (str[i] == '\0')
		return (i);
	else if (str[i] == PIPE)
	{
		log_printf("PIPE ");
		i++;
	}
	else if (str[i] == REDIR_I)
	{
		log_printf("REDIR_I ");
		i++;
	}
	else if (str[i] == REDIR_O)
	{
		log_printf("REDIR_O ");
		i++;
	}
	return (i);
}

void	printTokenType(t_list *token)
{
	enum TokenType	type;

	if (token->content != NULL)
	{
		type = (enum TokenType)(uintptr_t)(token->content);
		switch (type)
		{
		case COMMAND_T:
			printf("COMMAND_T\n");
			break ;
		// Add cases for other enum values as needed
		default:
			printf("Unknown TokenType\n");
		}
	}
	else
	{
		printf("Token content is NULL\n");
	}
}

int	getToken(char *str, int i, t_list *token)
{
	if (ft_iswhitespace(str[i]))
		i++;
	if (ft_isalpha(str[i]) || str[i] == '-')
	{
		while (str[i] != '\0' && ft_isalpha(str[i]) || str[i] == '-')
			i++;
		token->content = (void *)TokenType;
		// ((TokenType)token)->content = COMMAND_T;
		printTokenType(token);
		log_printf("WORD ");
	}
	// else if (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE)
	// i = quotes_parser(str, str[i], i);
	else if (ft_strchr("<>|", str[i]))
		i = ft_isspecial(str, i);
	else
		i++;
	return (i);
}

// TODO: Je passe ma cmd,
// je la remplis et apres je la rajoute a ma linked list Dois penser a proteger
// si NULL pour ne pas derefencer un pointer NULL
void	tokenizer(char *str, t_list **head)
{
	t_cmd			*cmd;
	t_list			*node;
	static int		i;
	static t_list	*token;

	i = 0;
	while (str[i] != '\0')
	{
		ft_lstnew(token);
		token = safe_calloc(1, sizeof(t_list));
		i = getToken(str, i, token);
		ft_lstadd_front(head, token);
		// log_printf("%d ", i);
		// i++;
	}
	return ;
}
