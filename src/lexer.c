/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:37:22 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/20 09:27:33 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	quotes_parser(const char *str, int i, t_token *token, int delimiter)
{
	int	j;

	j = i;
	while (str[i] != '\0' && str[i] != delimiter)
		i++;
	if (str[i] == '\0') // TODO: ERROR
	{
		printf("Missing quotes\n");
		return (-1);
	}
	token->type = ALPHA_T;
	if (delimiter == DOUBLE_QUOTE)
		token->value = parse_env(ft_substr(str, j, (i - j)));
	// TODO: Occasione un leaks sur mon pc
	else
		token->value = ft_substr(str, j, i - j);
	token->len = i - j;
	if (str[i + 1] >= 33)
		token->append = 1;
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
			return (i++);
		}
	}
	else if (str[i] == REDIR_O)
	{
		token->type = REDIR_OUT_T;
		if (str[i + 1] == REDIR_O)
		{
			token->type = REDIR_AP_T;
			return (i++);
		}
	}
	return (i);
}

static int	alpha_token(const char *str, int i, t_token *token)
{
	int	j;
	int	flag;

	flag = 0;
	j = i;
	while (str[i] != '\0' && !is_white_space(str[i]) &&
			!ft_strchr("\'\"<>|", str[i]))
	{
		if (str[i] == '$')
			flag = 1;
		i++;
	}
	if (flag == 1)
		token->value = parse_env(ft_substr(str, j, i - j));
	// TODO: Occasione un leaks sur mon pc
	else
		token->value = ft_substr(str, j, i - j);
	token->type = ALPHA_T;
	token->len = i - j;
	if (str[i] >= 33)
		token->append = 1;
	return (i);
}

static int	get_token(const char *str, int i, t_token *token)
{
	int	j;

	if (str[i] == '\0')
		return (i);
	else if (is_white_space(str[i]))
		return (i);
	else if (ft_strchr("<>|", str[i]))
		return (meta_token(str, i, token));
	else if (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE)
		return (quotes_parser(str, i + 1, token, str[i]));
	else
		return (alpha_token(str, i, token));
}

static void append_token(t_token *token, char **copy)
{
    static char *temp;

    if (token->append == 1)
    {
        if (*copy == NULL)
            *copy = ft_strdup(token->value);
        else
        {
            temp = *copy;
            *copy = ft_strjoin(*copy, token->value);
            free(temp);
        }
    }
    else if (token->type == ALPHA_T && token->append == 0 && *copy != NULL)
    {
        char *new_value = ft_strjoin(*copy, token->value);
        free(*copy);
        *copy = NULL;
        free(token->value);
        token->value = new_value;
    }
}

t_list	*tokenizer(const char *str, t_list *token_list)
{
	int		i;
	int		len;
	t_token	*token;
  char *copy;

	i = 0;
	len = ft_strlen(str);
	token = NULL;
  copy = NULL;
	while (i < len)
	{
		token = safe_calloc(1, sizeof(t_token));
		i = get_token(str, i, token);
		if (i == -1)
		{
			lexer_error(130, token_list, print_token);
			free(token);
			break ;
		}
		if (token->type == ALPHA_T)
			append_token(token, &copy);
		if (token->append != 1)
			ft_lstadd_back(&token_list, ft_lstnew((t_token *)token));
		else
		{
			free(token->value);
			free(token);
		}
		i++;
	}
  free(copy);
	i = syntax_parser(token_list);
	if (i == -1)
		lexer_error(2, token_list, print_token);
	return (token_list);
}
