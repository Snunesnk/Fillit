# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snunes <snunes@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 12:37:58 by snunes            #+#    #+#              #
#    Updated: 2019/06/05 20:49:57 by snunes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libft.a
SRC_PATH = .
SRC_NAME = ft_putchar.c ft_putstr.c ft_putchar_fd.c ft_putstr_fd.c ft_isdigit.c \
		ft_isalpha.c ft_bzero.c ft_memalloc.c ft_memdel.c ft_strlen.c \
		ft_strnew.c ft_strcat.c ft_strcpy.c ft_strsub.c ft_atoi.c ft_putnbr.c \
		ft_memcpy.c ft_lstdel.c ft_lstdelone.c ft_lstadd.c ft_lstnew.c \
		ft_putnbr_fd.c ft_lstiter.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_itoa.c ft_memccpy.c ft_lstmap.c ft_memmove.c \
		ft_memset.c ft_putendl_fd.c ft_putendl.c ft_tolower.c ft_toupper.c \
		ft_strchr.c ft_strclr.c ft_strcmp.c ft_strdel.c ft_strdup.c ft_strequ.c\
		ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strmap.c \
		ft_strmapi.c ft_strncat.c ft_strncpy.c ft_strnequ.c ft_strnstr.c \
		ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strtrim.c ft_memchr.c \
		ft_memcmp.c ft_isspace.c ft_strncmp.c ft_isupcase.c ft_strjoin_free.c \
		ft_strndup.c ft_strjoin_fclr.c ft_abs.c ft_islowcase.c get_next_line.c \
		ft_lst_length.c ft_sqrt.c
OBJ_PATH = obj
I_PATH = .
HEADER_NAME = libft.h
LDFLAGS = -Llibft
LDLIBS = -lft
OBJ_NAME = $(SRC_NAME:.c=.o)
CCFLAGS = -Wall -Wextra -Werror
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
HEADER = $(addprefix $(I_PATH)/,$(HEADER_NAME))

.PHONY : all, clean, fclean, re, help

## all		: compile et cree l'executable
all : $(NAME)

$(NAME) : $(OBJ)
	@ar -rc $@ $^
	@ranlib $@

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
