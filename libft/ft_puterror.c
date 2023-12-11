/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:00:58 by ldufour           #+#    #+#             */
/*   Updated: 2023/11/17 08:46:54 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puterror(int function, char *str)
{
	if (!str)
		str = strerror(errno);
	if (function == -1)
	{
		printf("Error: %s\n", str);
		exit(EXIT_FAILURE);
	}
}
