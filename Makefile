SRC=main.c  mutex.c vec.c ft_memmove.c
OBJ=$(SRC:.c=.o)
CFLAGS= -g3  -fsanitize=thread 
CC=cc
NAME=philo

lib=garb/garb.a



all: $(NAME)

$(NAME): $(lib) $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $^ $(lib)

$(lib):
	make -C garb

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C garb clean

fclean: clean
	rm -f $(NAME)
	make -C garb fclean

re: fclean all 
	make -C garb re