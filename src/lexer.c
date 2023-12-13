/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:37:22 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/12 14:47:42 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO: need more testing
void	quotes_parser(char *str, int c)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			j = i + 1;
			while (c != '\0' &&
					(!ft_iswhitespace(c) && !ft_strchr("<>|", c)))
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
	log_printf("%s", ft_substr(str, 0, i));
}

char	*ft_isspecial(char *str, int c)
{
	if (*str == '\0')
	{
		return (str); // Base case: end of string reached
	}
	if (c == PIPE)
	{
		log_printf("PIPE ");
		return (str);
	}
	// else if (c == REDIR_I)
	// {
	// 	if (*(str + 1) == REDIR_I)
	// 	{
	// 		log_printf("HEREDOC ");
	// 		return (&(*(str +1)));
	// 	}
	// 	else
	// 		log_printf("REDIR_I ");
	// 	if (str[j + 1] == ' ')
	// 		j++;
	// 	else
	// 		log_printf("Invalid filename");
	// 	while (c != '\0')
	// 	{
	// 		if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
	// 			j++;
	// 		else if (c == SPACE || c == '\t' || c == '\n')
	// 			j++;
	// 		while (isalpha(c))
	// 			j++;
	// 		j++;
	// 	}
	// }
	// else if (c == REDIR_O)
	// {
	// 	if (str[j + 1] == REDIR_O)
	// 	{
	// 		log_printf("APPEND ");
	// 		j++;
	// 		return (j);
	// 	}
	// 	else
	// 		log_printf("REDIR_O ");
	// }
	// else if (c == ' ')
	// 	log_printf("SPACE ");
	// else if (c == '\t') // Use '\t' for tab
	// 	log_printf("TAB ");
	// else if (c == '\n') // Use '\n' for newline
	// 	log_printf("NEWLINE ");
	// else if (c == SINGLE_QUOTE)
	// 	log_printf("SINGLE_QUOTE ");
	// else if (c == DOUBLE_QUOTE)
	// 	log_printf("DOUBLE_QUOTE ");
	return (ft_isspecial(str + 1, c));
}

void	*getToken(char *str, int *i, t_cmd *cmd)
{
  if (*i == 0)
  {
    while (ft_isalpha((unsigned char)str[*i]))
     (*i)++;
    cmd->token_type = COMMAND_T;
    log_printf("COMMAND");

  }
	// if (*str == DOUBLE_QUOTE || *str == SINGLE_QUOTE)
	// {
	// 	quotes_parser(str, *str);
	// }
	// else if (ft_strchr("<>|", *str))
	// {
	// 	ft_isspecial(str, *str);
	// }
	return (NULL);
}

// TODO: Je passe ma cmd,
// je la remplis et apres je la rajoute a ma linked list Dois penser a proteger si NULL pour ne pas derefencer un pointer NULL
void	tokenizer(char *str, t_list **head)
{
	t_cmd		*cmd;
	t_list		*node;
	static int	i;

	i = 0;
	while (str[i] != '\0')
	{
		cmd = (t_cmd *)safe_calloc(1, sizeof(t_cmd));
		cmd = getToken(str, &i, cmd);
    i++;
	}
	return ;
}
