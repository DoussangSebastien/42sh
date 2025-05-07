##
## EPITECH PROJECT, 2024
## edgar
## File description:
## Makefile
##

SRC		=	my_str_to_word_array_n.c \
			my_strlen.c \
			add_str.c \
			my_strstr.c \
			my_free_word_array.c \
			is_alpha.c \
			my_strcat.c \
			is_alphanumeric.c \
			my_strdup.c \
			my_putstr.c \
			my_duptab.c \
			my_getnbr.c \
			my_strcmp.c \
			my_put_nbr.c

OBJ = $(SRC:.c=.o)

NAME = libmy.a

HEADER = my.h

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../../
	cp include/$(HEADER) ../../include

clean:
	rm -f $(OBJ)
	rm -f ../../$(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean
