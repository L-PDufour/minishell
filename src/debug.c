/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:38:41 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/15 11:00:48 by ldufour          ###   ########.fr       */
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
