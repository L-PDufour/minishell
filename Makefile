# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldufour <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 08:17:58 by ldufour           #+#    #+#              #
#    Updated: 2023/12/11 15:05:48 by ldufour          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = gcc
CFLAGS	:= -g # -Wall -Wextra -Werror 

HEADERS	:= -I ./include -lreadline  
SRCS	:= $(wildcard src/*.c) $(wildcard src/builtin/*.c)  
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
re:		fclean all

