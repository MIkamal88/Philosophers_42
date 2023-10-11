# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/16 11:32:16 by m_kamal           #+#    #+#              #
#    Updated: 2023/07/16 11:32:17 by m_kamal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = ./src/
SRC = $(SRC_DIR)main.c\
			$(SRC_DIR)error.c\
			$(SRC_DIR)init.c\
			$(SRC_DIR)input.c\
			$(SRC_DIR)utils.c\
			$(SRC_DIR)actions.c\
			$(SRC_DIR)threads.c\
			$(SRC_DIR)cycle.c\

OBJ_DIR = ./ofiles/
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CC = gcc #-fsanitize=address
CF = -Wall -Wextra -Werror -pthread -g
RM = rm -rf



all : $(NAME)

$(NAME): ANNOUNCE $(OBJ)
	@printf "$(GR)Objects ready!$(RC)\n"
	@printf "\n$(CY)Compiling philosophers executable...$(RC)\n"
	$(CC) $(CF) $(OBJ) -o $(NAME)
	@printf "$(GR)Done!$(RC)\n\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CF) -c $< -o $@

ANNOUNCE:
	@printf "$(YE)Generating .o Files...$(RC)\n"

re :	fclean all

clean :
	@$(RM) $(OBJ) $(OBJ_DIR)
	@printf "$(RE)Object files removed!$(RC)\n"

fclean:	clean
	@$(RM) $(NAME)
	@printf "$(RE)Executable removed!$(RC)\n"

leak :			all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) 3 1500 400 300 4

helgrind:		all
	valgrind --tool=helgrind --history-level=full ./$(NAME) 4 310 200 200 5
.PHONY : all clean fclean re

.SILENT: $(NAME) $(OBJ)

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m
