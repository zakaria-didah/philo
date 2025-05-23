SRC=garb.c garb_utils.c garb_arena.c utiles.c 
OBJ=$(SRC:.c=.o)
CFLAGS= -g3 -Wall -Wextra -Werror
CC=cc
NAME=garb.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

