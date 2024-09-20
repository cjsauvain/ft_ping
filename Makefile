NAME = ft_ping

SRC =	main.c		\
		parsing.c	\
		ft_ping.c	\

HEADERS = include/ft_ping.h

INCLUDE_FOLDER = -I include/

SRCS =	$(addprefix src/, $(SRC))

OBJS_PATH = objects/

OBJ = $(SRCS:%.c=$(OBJS_PATH)%.o)

OBJS =  $(subst src/,,$(OBJ))

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

$(OBJS_PATH)%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE_FOLDER) -c $< -o $(subst src/,,$(<:%.c=$(OBJS_PATH)%.o))

all: $(NAME)

objects:
	@mkdir $(OBJS_PATH)

$(NAME): objects $(OBJ)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
