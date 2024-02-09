# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 23:35:16 by aschmitt          #+#    #+#              #
#    Updated: 2024/02/09 13:52:02 by aschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

INC				= inc/
SRC_DIR			= srcs/
OBJ_DIR			= obj/

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -I
RM				= rm -f

SRC 			= $(SRC_DIR)philo.c

OBJ 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

G = "\033[32m"
X = "\033[0m"

all: 		$(NAME)

$(NAME): 		$(OBJ)
				@echo $(G)Compiling [$(SRC)]$(X) 
				@$(CC) -o $(NAME) $(OBJ)
				@echo $(G)Compiling [$(NAME)]$(X)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
				@$(RM) -r $(OBJ_DIR)

fclean: 		clean
				@$(RM) $(NAME)  $(NAMEBONUS) 

re: 			fclean all

.PHONY: 		all clean fclean re