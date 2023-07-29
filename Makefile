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

SRC = ./main.c ./error.c ./init.c ./input.c ./input_utils.c ./utils.c

OBJ_PATH = ./ofiles/
OBJ = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))

CC = gcc -g
CF = -Wall -Wextra -Werror -pthread
RM = rm -rf

$(OBJ_PATH)%.o: %.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CF) -c $< -o $@

$(NAME): ANNOUNCE $(OBJ)
	@printf "$(GR)Objects ready!$(RC)\n"
	@printf "\n$(CY)Compiling philosophers executable...$(RC)\n"
	$(CC) $(CF) $(OBJ) -o $(NAME)
	@printf "$(GR)Done!$(RC)\n\n"

all : $(NAME)

ANNOUNCE:
	@printf "$(YE)Generating .o Files...$(RC)\n"

re :	fclean all

clean :
	@$(RM) $(OBJ) $(OBJ_PATH)
	@printf "$(RE)Object files removed!$(RC)\n"

fclean:	clean
	@$(RM) $(NAME)
	@printf "$(RE)Executable removed!$(RC)\n"

leak :			all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) 4 310 200 200 5

.PHONY : all clean fclean re

.SILENT: $(NAME) $(OBJ)

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m
