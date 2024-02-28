# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 23:35:16 by aschmitt          #+#    #+#              #
#    Updated: 2024/02/28 13:00:44 by aschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

INC				= inc/
SRC_DIR			= srcs/
OBJ_DIR			= obj/

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3 -I $(INC)
RM				= rm -f

SRC 			= $(SRC_DIR)philo.c $(SRC_DIR)check_dead.c $(SRC_DIR)utils2.c  $(SRC_DIR)utils.c $(SRC_DIR)to_print.c $(SRC_DIR)main.c   

OBJ 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

G = "\033[32m"
X = "\033[0m"

all: 		$(NAME)

$(NAME): 		$(OBJ)
				@echo $(G)Compiling [$(SRC)]$(X) 
				@$(CC) -o $(NAME) $(OBJ) -pthread
				@echo $(G)Compiling [$(NAME)]$(X)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(INC)*.h makefile
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS)  -c $< -o $@

clean:
				@$(RM) -r $(OBJ_DIR)

fclean: 		clean
				@$(RM) $(NAME)  $(NAMEBONUS) 

re: 			fclean all

.PHONY: 		all clean fclean re