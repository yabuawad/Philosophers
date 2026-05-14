CC = cc

CFLAGS = -Wall -Wextra -Werror -g -pthread

NAME = philo

SRC = activities.c \
	  main.c \
	  helpers.c \
	  printers.c \
	  threader.c \
	  initialise.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re