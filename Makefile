##
## EPITECH PROJECT, 2022
## B-SYN-400-LYN-4-1-abstractVM-florian.kamps
## File description:
## Makefile
##


SRC	=	src/Factory.cpp	\
		src/main.cpp	\
		src/Parser.cpp	\
		src/VirtualMachine.cpp	\

OBJ	=	$(SRC:.c=.o)

NAME	=	abstractVM

all:	$(NAME)

$(NAME): clean
	g++ $(SRC) -I include -o $(NAME) -g3 -std=c++2a

clean:
	rm -f *.o

fclean:	clean
	rm -f $(NAME)

re:	fclean all