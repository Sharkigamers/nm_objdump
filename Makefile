##
## EPITECH PROJECT, 2019
## minishell1
## File description:
## Makefile
##

NAMEOBJDUMP		=		my_objdump

NAMENM			=		my_nm

all:	objdump nm

tests_run:	$(TEST)
	$(CC) -o unit_tests $(TEST) -lcriterion --coverage
	./unit_tests | gcovr

objdump:
	cd src/objdump && make && mv $(NAMEOBJDUMP) ../../

nm:
	cd src/nm && make && mv $(NAMENM) ../../

clean:
	cd src/nm && make clean
	cd src/objdump && make clean

fclean:
	cd src/nm && make fclean
	cd src/objdump && make fclean
	rm -f $(NAMENM)
	rm -f $(NAMEOBJDUMP)

re:	fclean all

.PHONY: all tests_run clean fclean re
