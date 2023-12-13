/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:37:22 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/13 11:14:56 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO: need more testing
int	quotes_parser(char *str, int c, int i)
{
	int	j;
  int k;

  j = i;
  k = i;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			j = i + 1;
			while (str[j] != '\0' && (!ft_iswhitespace(str[j]) && !ft_strchr("<>|", str[j])))
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
		return (i); // Base case: end of string reached
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

int	getToken(char *str, int i, t_cmd *cmd)
{
	if (ft_iswhitespace(str[i]))
		i++;
	if (ft_isalpha(str[i]))
	{
		while (str[i] != '\0' && ft_isalpha(str[i]))
			i++;
		log_printf("COMMAND ");
	}
	else if (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE)
		i = quotes_parser(str, str[i], i);
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
	t_cmd		*cmd;
	t_list		*node;
	static int	i;

	i = 0;
	while (str[i] != '\0')
	{
		cmd = (t_cmd *)safe_calloc(1, sizeof(t_cmd));
		i = getToken(str, i, cmd);
		// log_printf("%d ", i);
		// i++;
	}
	return ;
}
