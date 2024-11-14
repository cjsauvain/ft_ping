NAME = ft_ping

SRC	=	parsing.c	\
		ft_ping.c	\
		main.c		\

HEADERS = include/ft_ping.h

INCLUDE_FOLDER = -I include/

SRCS =	$(addprefix src/, $(SRC))

OBJS_PATH = objects/

OBJ = $(SRCS:%.c=$(OBJS_PATH)%.o)

OBJS = $(subst objects/,,$(OBJ))

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

$(OBJS_PATH)%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE_FOLDER) -c $< -o $(subst src/,,$@)

all: $(NAME)

objects:
	@mkdir $(OBJS_PATH)

$(NAME): objects $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_FOLDER) -o $(NAME)

clean:
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
