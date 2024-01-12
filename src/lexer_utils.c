/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 09:17:34 by ldufour           #+#    #+#             */
/*   Updated: 2024/01/12 10:04:40 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quotes_parser(const char *str, int i, t_token *token, int *status)
{
	int	j;
	int	flag;
	int	delimiter;

	flag = 0;
	delimiter = str[i];
	i = i + 1;
	j = i;
	while (str[i] != '\0' && str[i] != delimiter)
	{
		if (str[i] == '$')
			flag = 1;
		i++;
	}
	if (str[i] == '\0')
		*status = 130;
	token->type = ALPHA_T;
	if (delimiter == DOUBLE_QUOTE && flag == 1)
		token->value = parse_env(ft_substr(str, j, (i - j)));
	else
		token->value = ft_substr(str, j, i - j);
	if (str[i + 1] >= 33 && !ft_strchr("<>|", str[i + 1]))
		token->append = true;
	return (++i);
}
