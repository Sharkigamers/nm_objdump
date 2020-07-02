##
## EPITECH PROJECT, 2019
## nm
## File description:
## Makefile
##

SRC		=		$(shell find ./ -name '*.c' ! -name unit_tests.c)	\

OBJ		=		$(SRC:.c=.o)

CC		=		gcc -I./include

NAME	=		my_nm

C_FLAGS	=	-W -Wall -Wextra

all:	nm

nm:	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(shell find ./ -name '*.o')
	rm -f $(shell find ./ -name '*~')
	rm -f $(shell find ./ -name '*#')
	rm -f $(shell find ./ -name '*vg*')
	rm -f $(shell find ./ -name '*.gc*')

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
