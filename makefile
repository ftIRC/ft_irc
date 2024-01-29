SRCS = *.cpp */*.cpp
INCS = incs

NAME = ircserv
NAME = a.out
CXXFLAGS =
CC = c++
RM = rm -rf

all :
	$(CC) $(CXXFLAGS) -I $(INCS) -o $(NAME) $(SRCS)

clean :
	$(RM) *.o

fclean :
	make clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
	