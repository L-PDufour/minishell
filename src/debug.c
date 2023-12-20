/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:38:41 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/20 08:51:16 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	log_printf(const char *format, ...)
{
	FILE	*logFile;
	va_list	args;

	logFile = fopen("logfile", "a");
	if (logFile == NULL)
	{
		fprintf(stderr, "Error opening log file!\n");
		return ;
	}
	va_start(args, format);
	vfprintf(logFile, format, args);
	va_end(args);
	fclose(logFile);
}

void	print_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token->value)
  {
		log_printf("(%s)", token->value);
    // log_printf("(%i)", token->append);
  }
	else
		log_printf("(%c)", (char)token->type);
}

void	print_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	log_printf("Command Table:\n");
	for (int i = 0; cmd->cmd_table[i] != NULL; ++i)
	{
		log_printf("  %s\n", cmd->cmd_table[i]);
	}
	log_printf("Expandable: %d\n", cmd->expandable);
	log_printf("Input File: %s\n", cmd->infile ? cmd->infile : "N/A");
	log_printf("Output File: %s\n", cmd->outfile ? cmd->outfile : "N/A");
	log_printf("Input FD: %d\n", cmd->fd_input);
	log_printf("Output FD: %d\n", cmd->fd_output);
	log_printf("Pipe FDs: %d (read) / %d (write)\n", cmd->pipe[0],
			cmd->pipe[1]);
}

void	tester_ms(char *str, t_list *token_list, t_list *cmd_list)
{
	log_printf("STR = %s\n", str);
	token_list = tokenizer(str, token_list);
	ft_lstiter(token_list, &print_token);
	log_printf("\n");
	// cmd_list = parser(cmd_list, token_list);
	ft_lstiter(cmd_list, &print_cmd);
	log_printf("\n");
	ft_lstclear(&token_list, free_token);
	// ft_lstclear(&cmd_list, free_cmd);
	log_printf("\n");
}
