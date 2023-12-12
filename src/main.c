/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2023/12/08 16:12:08 by ldufour          ###   ########.fr       */
/*   Updated: 2023/12/12 09:16:04 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
  t_command cmd;
  char *cmd_str;

  (void)argc;
  (void)argv;
  while (true) {
    cmd_str = display_prompt();
    cmd_str = trim_str(cmd_str);
    if (strcmp(cmd_str, "")) {
      parse_cmd(cmd_str, &cmd);
      // printf("name: %s\n", cmd.name);
      // printf("opt: %s\n", cmd.option);
      // printf("opt2: %s\n", cmd.option2);
      exec_cmd(cmd, envp);
    }
  }
  free(cmd_str);
  return (0);
}

// Pseudo code
// cmd_line = readline
// while cmd_line
// malloc struct node
// struct.type = getToken(cmd_line)
// getGrammar(struct, cmd_line)
// cmd_line++
