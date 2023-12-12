/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:37:22 by ldufour           #+#    #+#             */
/*   Updated: 2023/12/12 08:57:08 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void getToken(char *str, int i, t_list *head) {}
// TODO Je passe ma cmd, je la remplis et apres je la rajoute a ma linked list
// Dois penser a proteger si NULL pour ne pas derefencer un pointer NULL
void recursive_tokenizer(char *str, int i, t_list **head) {
  t_cmd *cmd;
  t_list *node;

  if (!str || str[i] == '\0')
    return;
  node = ft_lstnew(cmd);
  getToken(str, i, *head);
  ft_lstadd_front(head, (void *)cmd);
  recursive_tokenizer(str, i, head);
  return;
}

// TODO: need more testing
void quotes_parser(char *str, int c) {
  int i;
  int j;

  i = 0;
  while (str[i] != '\0') {
    if (str[i] == c) {
      j = i + 1;
      while (str[j] != '\0' &&
             (!ft_iswhitespace(str[j]) && !ft_strchr("<>|", str[j]))) {
        j++;
      }
      if (str[j] == '\0') {
        printf("quote error\n");
        break;
      }
    }
    i++;
  }
  printf("%s", ft_substr(str, 0, i));
}
