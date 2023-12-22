# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 08:17:58 by ldufour           #+#    #+#              #
#    Updated: 2023/12/22 19:01:49 by ldufour          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= minishell
CC					= gcc
CFLAGS				= -g #-Wall -Wextra -Werror
RM					= rm -rf
LIBFT				= $(LIBFT_DIR)/libft.a
SRC_DIR				= src
INC_DIR				= includes
LIBFT_DIR			= lib/libft
READLINE_DIR		= lib/readline-8.1
READLINE_LIB		= $(READLINE_DIR)/libreadline.a
READLINE_INC		= -I$(READLINE_DIR)/include
READLINE_URL		= ftp://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz

INC					= -I$(INC_DIR) -I$(LIBFT_DIR) $(READLINE_INC)
LIBS				= -lncurses

SRC = $(shell find ./src -iname "*.c")

OBJ = $(SRC:.c=.o)

all: install $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(READLINE_LIB)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(INC)
	@echo $(CUT) $(CUT) 
	@echo $(BOLD)$(L_PURPLE) Notre minishell est plus mignon qu’un vrai shell  💪💥 $(RESET)	

$(READLINE_LIB): $(READLINE_DIR)
	@if [ ! -f "$@" ]; then \
		echo $(BOLD)$(PINK)"Building Readline 8.1 library..."$(MINT); \
		cd $(READLINE_DIR) && ./configure && make; \
		echo $(BOLD)$(GREEN)"Readline library built successfully"$(RESET); \
	else \
		echo $(BOLD)$(PINK)"Readline 8.1 library already exists, skipping build."$(RESET); \
	fi


$(READLINE_DIR):
	@mkdir -p $(READLINE_DIR)
	@test -f $(READLINE_DIR)/libreadline.a || { curl -L $(READLINE_URL) | tar xz -C $(READLINE_DIR) --strip-components=1; }
	@echo $(BOLD)$(GREEN) ✨ Readline 8.1 ✨ downloaded and extracted successfully. 💪💥 $(RESET)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC)
	@echo "Compiled $<"

readline-8.1_EXISTS := $(wildcard lib/readline-8.1)

install: $(READLINE_LIB)
	
norm:
	@echo $(BOLD)$(PINK)" Mandatory part!"$(MINT)
	@norminette $(SRC) $(INC_DIR)
	@echo $(BOLD)$(PINK)" Bonus part!"$(MINT)
	@norminette $(BONUS_SRC)

clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ)
	@echo $(BOLD)$(GREEN) Cleaned objects and executables! ... 🧹🗑️$(RESET)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME) 
	@echo $(BOLD)$(L_PURPLE) ✨minishell✨ $(PINK)All cleaned up! ....🧹🗑️$(RESET)
	
	



re: fclean all

.PHONY: all clean fclean re


########################## Color #########################

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
