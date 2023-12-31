/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:03:29 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/18 10:12:18 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void lexer_error(int c, t_list *head, void (*del)(void *))
{
		ft_lstclear(&head, del);
		exit(c);
}
