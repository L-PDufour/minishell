/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:38:41 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/12 12:55:19 by ldufour          ###   ########.fr       */
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

