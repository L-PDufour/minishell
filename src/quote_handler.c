/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:25:14 by joe_jam           #+#    #+#             */
/*   Updated: 2023/12/15 14:38:05 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quotes_parser(const char *str, int c, int i)
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
				printf("quote error\n");
				break ;
			}
		}
		i++;
	}
	printf("%s", ft_substr(str, k, j));
	return (i);
}
//TODO:
/* VALIDATION */
// delimiter = ' ou "
// if you find a delimiter increment the counter until you find the same delimiter

//check if the next char is a \ backslash (if its a backslash skip it and 
// keep incrementing and looking for the same delimiter
// if the closing delimiter is encoutered return 0 esle 1

/* PARSING */
/* 1-if the first delimiter found is ' then  extract the string until next delimiter
 without the delimiter and write it as it is
/* 2-if the first delimiter found is " then  extract the string until next delimiter
 without the delimiter and pass it to parse env





*/

//TODO:
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