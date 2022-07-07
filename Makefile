##
## EPITECH PROJECT, 2022
## B-PDG-300-LYN-3-1-PDGD04am-julien.deviller
## File description:
## Makefile
##

SRC	=	Parser.cpp	\
		main.cpp	\

OBJ	=	$(SRC:.c=.o)

NAME	=	V0

all:	$(NAME)

$(NAME):
	g++ $(SRC) -I include -o $(NAME) -g3 -std=c++2a

clean:
	rm -f *.o

fclean:	clean
	rm -f $(NAME)

re:	fclean all
