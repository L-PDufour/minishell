/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:18:08 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/21 15:39:51 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token(void *token_ptr)
{
	t_token	*token;

	if (!token_ptr)
		return ;
	token = (t_token *)token_ptr;
	free(token->value);
	free(token);
}

void	free_cmd(void *cmd)
{
	t_cmd	*typed_cmd;
	int		i;

	if (!cmd)
		return ;
	typed_cmd = (t_cmd *)cmd;
	if (typed_cmd->cmd_table)
	{
		i = 0;
		while (typed_cmd->cmd_table[i] != NULL)
		{
			free(typed_cmd->cmd_table[i]);
			i++;
		}
		free(typed_cmd->cmd_table);
	}
	free(typed_cmd->outfile);
	free(typed_cmd->infile);
	free(typed_cmd);
}

void	clean_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	exit_prg_at_error(char *str)
{
	printf("Error\n");
	if (str)
		printf("%s\n", str);
	exit(EXIT_FAILURE);
}