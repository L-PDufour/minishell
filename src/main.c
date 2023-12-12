/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2023/12/08 16:12:08 by ldufour          ###   ########.fr       */
/*   Updated: 2023/12/12 08:57:12 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool ft_iswhitespace(int c) {
  if (c == 32 || (c >= 9 && c <= 13))
    return (true);
  return (false);
}

void exit_prg_at_error(char *str) {
  printf("Error\n");
  if (str)
    printf("%s\n", str);
  exit(EXIT_FAILURE);
}

void *safe_calloc(size_t nmemb, size_t size) {
  void *ret;

  ret = ft_calloc(nmemb, size);
  if (!ret)
    exit_prg_at_error("Malloc failure");
  return (ret);
}

// TODO: Je crois que cette fonction sert à rien
t_list **init_struct(void) {
  static t_list **head;

  // static t_cmd	*command;
  // command = safe_calloc(1, sizeof(t_cmd));
  head = safe_calloc(1, sizeof(t_list *));
  // head = ft_lstnew(command);
  return (head);
}
int main(int argc, char **argv, char **envp) {
  char *cmd_line;
  t_list **head;
  static int i;

  cmd_line = "";
  i = 0;
  if (argc == 2)
    cmd_line = argv[1]; // Use argv[1] for the first command-line argument
                        // else
  quotes_parser(argv[1], '"');
  // cmd_line = readline("");
  // head = init_struct();
  // printf("%s\n", cmd_line);
  // recursive_tokenizer(cmd_line, i, head);
  // ((t_cmd *)head->content)->infile = strdup("test");
  // printf("%s\n", ((t_cmd *)head->content)->infile);
  return (0);
}

// Pseudo code
// cmd_line = readline
// while cmd_line
// malloc struct node
// struct.type = getToken(cmd_line)
// getGrammar(struct, cmd_line)
// cmd_line++
