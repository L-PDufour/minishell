/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:25:14 by joe_jam           #+#    #+#             */
/*   Updated: 2024/01/09 16:09:57 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quotes_parser(const char *str, int i, t_token *token, int delimiter)
{
	int	j;
	int	flag;

	flag = 0;
	j = i;
	while (str[i] != '\0' && str[i] != delimiter)
	{
		if (str[i] == '$')
			flag = 1;
		i++;
	}
	if (str[i] == '\0') // TODO: ERROR
	{
		printf("Missing quotes\n");
		return (-1);
	}
	token->type = ALPHA_T;
	// TODO: En commentaire le temps de regler les leaks
	if (delimiter == DOUBLE_QUOTE && flag == 1)
		token->value = parse_env(ft_substr(str, j, (i - j)));
	else
		token->value = ft_substr(str, j, i - j);
	token->len = i - j;
	if (str[i + 1] >= 33 && !ft_strchr("<>|", str[i + 1]))
		token->append = true;
	return (++i);
}
// TODO:
/* VALIDATION */
// delimiter = ' ou "
// if you find a delimiter increment the counter until you find the same
// delimiter

// check if the next char is a \ backslash (if its a backslash skip it and
//  keep incrementing and looking for the same delimiter
//  if the closing delimiter is encoutered return 0 esle 1

/* PARSING */
/* 1-if the first delimiter found is ' then  extract the string until next
delimiter without the delimiter and write it as it is

* 2-if the first delimiter found is " then  extract the string until next
delimiter without the delimiter and pass it to parse env





*/

// TODO:
/**
 * regarder la focnction quotes parser
 * tester la focnction quotes parser
 * integrer la fonction parse env avec "lexer.c"
 *
 *
 *
 *
 *
 * **/
