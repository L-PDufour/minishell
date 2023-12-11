# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldufour <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 08:17:58 by ldufour           #+#    #+#              #
#    Updated: 2023/12/11 14:53:44 by ldufour          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = gcc
CFLAGS	:= -g # -Wall -Wextra -Werror 

HEADERS	:= -I ./include -lreadline  
SRCS	:= $(wildcard(src/*.c) $(wildcard(src/builtin/*.c)  
OBJS	= ${SRCS:.c=.o}
LIBFT	= libft/libft.a
VALGRIND = valgrind
all: $(NAME)
	
%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) 

$(NAME): $(OBJS)
		@cd libft && make all
		@$(CC) $(OBJS) $(LIBFT) $(HEADERS) -o $(NAME)
clean:	
		@cd libft && make clean
		@rm -rf $(OBJS) 
		# @rm *.txt
fclean:	clean
		@cd libft && make fclean
		@rm -f $(NAME) 

run: all 
	@./minishell

norm :
	@echo $(BOLD)$(PINK)" Mandatory part!"$(MINT)
	@norminette $(SRCS) $(INC_DIR)
	@echo $(BOLD)$(PINK)" Bonus part!"$(MINT)

leaks:
	leaks --atExit -- ./minishell | cat -e

re: fclean all 

.PHONY: all clean fclean re

# ######################### Color #########################

GREEN="\033[32m"
MINT="\033[38;5;51m"
L_PURPLE="\033[38;5;55m"
MAUVE="\033[38;5;147m"
PINK="\033[38;5;175m"
RESET="\033[0m"
BOLD="\033[1m"
UP = "\033[A"
DOWN = "\033[B"
RIGHT = "\033[C"
LEFT = "\033[D"
CUT = "\033[K"
SAVE = "\033[s"
RESTORE = "\033[u"

.PHONY: all, clean, fclean, re, libmlx
