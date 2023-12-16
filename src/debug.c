/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:38:41 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/16 14:41:41 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	log_printf(const char *format, ...)
{
	FILE	*logFile;
	va_list	args;

	// Open or create a log file in append mode
	logFile = fopen("logfile", "a");
	if (logFile == NULL)
	{
		fprintf(stderr, "Error opening log file!\n");
		return ;
	}
	// Use a va_list to handle variable arguments
	va_start(args, format);
	// Print to the log file
	vfprintf(logFile, format, args);
	// Clean up
	va_end(args);
	// Close the log file
	fclose(logFile);
}

// Function to print the linked list of tokens
void	print_token_list(t_list *head)
{
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		log_printf("T = %c\n", (char)((t_token *)current->content)->type);
		if (((t_token *)current->content)->value)
			log_printf("v = %s\n", ((t_token *)current->content)->value);
		current = current->next;
	}
}


void print_cmd_list(t_list *head)
{
    t_list *current = head;

    while (current != NULL)
    {
        t_cmd *cmd = (t_cmd *)current->content;

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
        log_printf("Pipe FDs: %d (read) / %d (write)\n", cmd->pipe[0], cmd->pipe[1]);

        current = current->next;
    }
}

