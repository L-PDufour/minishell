# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 08:17:58 by ldufour           #+#    #+#              #
#    Updated: 2024/01/15 21:42:19 by joe_jam          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = minishell
CC              = gcc
CFLAGS          = -g #-Wall -Wextra -Werror
RM              = rm -rf
LIBFT           = $(LIBFT_DIR)/libft.a
SRC_DIR         = src
INC_DIR         = includes
LIBFT_DIR       = lib/libft
READLINE_DIR    = lib/readline-8.2
READLINE_LIB    = $(READLINE_DIR)/libreadline.a
READLINE_INC    = -I$(READLINE_DIR)/include
READLINE_URL    = https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
READLINE_SRC	= lib/readline-8.2.tar.gz

INC             = -I$(INC_DIR) -I$(LIBFT_DIR) $(READLINE_INC)
LIBS            = -lncurses -L$(READLINE_DIR) -lreadline -lhistory


SRC = $(SRC_DIR)/main.c $(SRC_DIR)/debug.c $(SRC_DIR)/lexer.c $(SRC_DIR)/parser.c $(SRC_DIR)/prompt.c $(SRC_DIR)/builtin/pwd.c $(SRC_DIR)/free_and_exit.c\
      $(SRC_DIR)/utils.c $(SRC_DIR)/builtin/cd.c $(SRC_DIR)/builtin_execution.c $(SRC_DIR)/env_utils.c $(SRC_DIR)/command_execution.c $(SRC_DIR)/l_error.c $(SRC_DIR)/leon_bouette.c\
      $(SRC_DIR)/builtin/echo.c  $(SRC_DIR)/builtin/env.c  \
      $(SRC_DIR)/builtin/built_exit.c  $(SRC_DIR)/lexer_utils.c $(SRC_DIR)/signals.c\

OBJ = $(SRC:.c=.o)

all: install $(NAME)

$(READLINE):
	@if [ ! -d "$(READLINE_DIR)" ] ; then \
		curl $(READLINE_URL) -o $(READLINE_SRC) ; \
		tar -xvf $(READLINE_SRC) -C $(LIB_DIR); \
		rm $(READLINE_SRC) ; \
	fi
	@cd $(READLINE_DIR) ; \
	./configure ; \
	make 

$(NAME): $(OBJ) $(LIBFT) $(READLINE)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(INC)
	@printf "$(CUT) $(CUT) "
	@printf "$(BOLD)$(L_PURPLE) Notre minishell est plus mignon qu’un vrai shell  💪💥 $(RESET)	\n"

$(READLINE_LIB): $(READLINE_DIR)
	@if [ ! -d "$(READLINE_DIR)" ] ; then \
		printf "$(BOLD)$(PINK)"Building Readline 8.2 library..."$(MINT); \"
		cd $(READLINE_DIR) && ./configure --prefix=$(CURDIR) && make; \
		printf "$(BOLD)$(GREEN)"Readline library built successfully"$(RESET); \"
	else \
		printf "$(BOLD)$(PINK)"nothing to be done for all."$(RESET); \"
	fi

$(READLINE_DIR):
	@mkdir -p $(READLINE_DIR)
	@test -f $(READLINE_DIR)/libreadline.a || { curl -L $(READLINE_URL) | tar xz -C $(READLINE_DIR) --strip-components=1; }
	@printf "$(BOLD)$(GREEN) ✨ Readline 8.2 ✨ downloaded and extracted successfully. 💪💥 $(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC)
	@printf "$(BOLD)$(SKYBLUE) Compiled $(BOLD)$(PINK)$<$(RESET)\r" 

readline-8.2_EXISTS := $(wildcard lib/readline-8.2)

install: $(READLINE_LIB)
	
norm:
	@printf "$(BOLD)$(PINK) Mandatory part! $(MINT)\n"
	@norminette $(SRC) $(INC_DIR)
	@printf "$(BOLD)$(PINK) Bonus part! $(MINT)\n"
	@norminette $(BONUS_SRC)

clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ)
	@printf "$(BOLD)$(GREEN)Cleaned objects and executables! ...🧹🗑️$(RESET)\n"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME) 
	@printf "$(BOLD)$(L_PURPLE) ✨minishell✨ $(PINK)All cleaned up! ....🧹🗑️$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re

BOLD=$(shell tput bold)
L_PURPLE=$(shell tput setaf 5)
PINK=$(shell tput setaf 1)
GREEN=$(shell tput setaf 2)
MINT=$(shell tput setaf 6)
SKYBLUE=$(shell tput setaf 74)
RESET=$(shell tput sgr0)

