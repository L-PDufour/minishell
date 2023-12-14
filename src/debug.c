/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:38:41 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/14 09:41:49 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void log_printf(const char *format, ...)
{
    FILE *logFile;
    va_list args;

    // Open or create a log file in append mode
    logFile = fopen("logfile", "a");
    if (logFile == NULL)
    {
        fprintf(stderr, "Error opening log file!\n");
        return;
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

// Function to print the token type as a string
const char *token_type_to_str(t_tokentype type) {
    switch (type) {
        case ALPHA_T:
            return "ALPHA";
        case PIPE_T:
            return "PIPE";
        case REDIR_IN_T:
            return "REDIR_IN";
        case HERE_DOC_T:
            return "HERE_DOC";
        case REDIR_OUT_T:
            return "REDIR_OUT";
        case REDIR_AM_T:
            return "REDIR_AM";
        // Add more cases as needed
        default:
            return "UNKNOWN";
    }
}

// Function to print the linked list of tokens
void print_token_list(t_list *head) {
    t_list *current = head;

    while (current != NULL) {
        t_token *token = (t_token *)current->content;
        printf("Value: %s\n", token->value);
        current = current->next;
    }
}
