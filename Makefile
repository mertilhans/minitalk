NAME = minitalk
CFLAGS = -Wall -Wextra -Werror

SRC = client server
BONUS_SRC = client_bonus server_bonus

all : $(NAME)

bonus : $(BONUS_SRC)

$(NAME) : $(SRC)

clean :
	rm -f $(SRC) $(BONUS_SRC)

fclean : clean

re : fclean all

.PHONY : all clean fclean re