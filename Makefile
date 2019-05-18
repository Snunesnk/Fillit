# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snunes <snunes@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 12:37:58 by snunes            #+#    #+#              #
#    Updated: 2019/05/18 14:46:40 by snunes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = fillit
SRC_PATH = .
SRC_NAME = main.c check_file.c fillit.c valid_place.c
OBJ_PATH = obj
I_PATH = include
HEADER_NAME = fillit.h
LDFLAGS = -Llibft
LDLIBS = -lft
OBJ_NAME = $(SRC_NAME:%.c=%.o)
CCFLAGS = -Wall -Wextra -Werror
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
HEADER = $(addprefix $(I_PATH)/,$(HEADER_NAME))

.PHONY : all, clean, fclean, re, help

## all		: compile et cree l'executable
all : $(NAME)
	@cd libft && make

$(NAME) : $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

## objet		: verifie que les objets et le header soient a jour
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CCFLAGS) -I $(I_PATH) -o $@ -c $<

## clean		: efface tout les binaires
clean :
	@rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

## fclean		: efface les binaires ainsi que l'executable
fclean : clean
	@rm -fv $(NAME)

## re		: lance la regle "fclean", puis la regle "all"
re : fclean all

## norme		: verifie la norme du projet
norme :
	@norminette $(SRC)
	@norminette $(HEADER)

## help		: affiche les options disponibles et leurs utilitees
help : Makefile
	@sed -n 's/^##//p' $<
