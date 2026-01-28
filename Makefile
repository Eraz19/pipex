# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/23 23:39:56 by adouieb           #+#    #+#              #
#    Updated: 2026/01/28 11:25:54 by adouieb          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Output library name
NAME:=pipex

# Variable to catch norminette errors
NORM_ERRORS:=""

# Compiler and flags
CC:=cc
CC_FLAGS:=-Werror -Wextra -Wall

# Directories
HDR_DIR:=includes
SRC_DIR:=srcs
OBJ_DIR:=objs
LIB_DIR:=libft
TEST_DIR:=test

SRCS:=${SRC_DIR}/args/parse.c				\
		${SRC_DIR}/command/free.c			\
		${SRC_DIR}/command/constructor.c	\
		${SRC_DIR}/command/execute.c		\
		${SRC_DIR}/path/get_binaries_path.c	\
		${SRC_DIR}/pipe/free.c				\
		${SRC_DIR}/pipe/setup.c				\
		${SRC_DIR}/pipe/constructor.c		\
		${SRC_DIR}/debug.c					\
		${SRC_DIR}/main.c

OBJS=$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIB:=ft

# ============================================================================ #
#                                    RULES                                     #
# ============================================================================ #

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) -I $(HDR_DIR) -I $(LIB_DIR) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CC_FLAGS) -I $(LIB_DIR) -I $(HDR_DIR) -L $(LIB_DIR) $(OBJS) -lft -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	@bash $(TEST_DIR)/test.sh

.PHONY: all clean fclean re test