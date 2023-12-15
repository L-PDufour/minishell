/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:50:09 by joe_jam           #+#    #+#             */
/*   Updated: 2023/12/22 14:26:08 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_exit(t_command cmd)
{
	// sig_t				sig;
	// struct sigaction	sact;

	// sigemptyset(&sact.sa_mask);
	// sact.sa_flags = 0;
	// sact.sa_handler = SIG_IGN;
	// sigaction(SIGUSR2, &sact, NULL);
	// printf("before kill()");
	// kill(getpid(), SIGUSR2);
	// printf("after kill()");
	int signal;
	// signal()
	if (cmd.pid == 0)
	{
		// printf("my tgetnum is : %i\n", tgetnum("ttys001"));
		// printf("my current pid is : %i\n", cmd.pid);
		kill(cmd.pid, signal);
	}
	else
		exit(0);
	return (0);
}
