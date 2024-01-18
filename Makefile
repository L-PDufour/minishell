# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 08:17:58 by ldufour           #+#    #+#              #
#    Updated: 2024/01/18 13:38:53 by yothmani         ###   ########.fr        #
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
READLINE_DIR    = lib/readline-8.1
READLINE_LIB    = $(READLINE_DIR)/libreadline.a
READLINE_INC    = -I$(READLINE_DIR)/include
READLINE_URL    = ftp://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz

INC             = -I$(INC_DIR) -I$(LIBFT_DIR) $(READLINE_INC)
LIBS            = -lncurses -L$(READLINE_DIR) -lreadline -lhistory

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/debug.c $(SRC_DIR)/lexer.c $(SRC_DIR)/parser.c $(SRC_DIR)/prompt.c $(SRC_DIR)/builtin/pwd.c $(SRC_DIR)/free_and_exit.c\
      $(SRC_DIR)/utils.c $(SRC_DIR)/builtin/cd.c  $(SRC_DIR)/env_utils.c $(SRC_DIR)/command_execution.c $(SRC_DIR)/l_error.c\
      $(SRC_DIR)/builtin/echo.c  $(SRC_DIR)/builtin/env.c  \
      $(SRC_DIR)/builtin/built_exit.c $(SRC_DIR)/exec_utils.c $(SRC_DIR)/exec_list.c $(SRC_DIR)/lexer_utils.c $(SRC_DIR)/signals.c\
	  $(SRC_DIR)/builtin/export.c $(SRC_DIR)/builtin/unset.c $(SRC_DIR)/builtin_execution.c\

OBJ = $(SRC:.c=.o)


all: install $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(READLINE_LIB)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(INC)
	@echo $(CUT) $(CUT) 
	@echo $(BOLD)$(L_PURPLE) Notre minishell est plus mignon qu’un vrai shell  💪💥 $(RESET)	

$(READLINE_LIB): $(READLINE_DIR)
	@if [ ! -f "$@" ]; then \
		echo $(BOLD)$(PINK)"Building Readline 8.1 library..."$(MINT); \
		cd $(READLINE_DIR) && ./configure --prefix=$(CURDIR) && make; \
		echo $(BOLD)$(GREEN)"Readline library built successfully"$(RESET); \
	else \
		echo $(BOLD)$(PINK)"nothing to be done for all."$(RESET); \
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
