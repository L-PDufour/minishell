# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 08:17:58 by ldufour           #+#    #+#              #
#    Updated: 2023/12/13 18:06:03 by yothmani         ###   ########.fr        #
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

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/prompt.c $(SRC_DIR)/builtin/pwd.c\
$(SRC_DIR)/utils.c $(SRC_DIR)/builtin/cd.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(READLINE_LIB)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(INC)
	@echo $(CUT) $(CUT) 
	@echo $(BOLD)$(L_PURPLE) Notre minishell est plus mignon qu’un vrai shell  💪💥 $(RESET)


$(READLINE_LIB): $(READLINE_DIR)
	@echo $(BOLD)$(PINK)"Building Readline 8.1 library..."$(MINT)
	cd $(READLINE_DIR) && ./configure && make
	@echo $(BOLD)$(GREEN)"Readline library built successfully"$(BOLD)$(GREEN)$(RESET)

$(READLINE_DIR):
	@echo $(BOLD)$(L_PURPLE) Downloading and extracting Readline 8.1...   💪💥 $(RESET)
	@mkdir -p $(READLINE_DIR)
	@curl -L $(READLINE_URL) | tar xz -C $(READLINE_DIR) --strip-components=1
	@echo $(BOLD)$(GREEN) ✨ Readline 8.1 ✨ downloaded and extracted successfully. 💪💥 $(RESET)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC)
	@echo "Compiled $<"

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