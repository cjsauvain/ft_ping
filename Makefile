#Executable Name
NAME = ft_ping

#Directories
SRCS_DIR = srcs/
OBJS_DIR = objects/
INC_DIR  = include/

#Sources / Headers
SRC	=	main.c					\
		parsing.c				\
		ft_ping.c				\
		process_checksum.c		\
		send_echo_request.c		\
		receive_echo_reply.c	\
		create_icmp_packet.c	\
		create_socket.c			\
		initialize_addr.c		\

SRCS =	$(addprefix $(SRCS_DIR), $(SRC))
HEADERS = $(INC_DIR)ft_ping.h

#Objects
OBJS = $(subst $(SRCS_DIR),,$(SRCS:%.c=$(OBJS_DIR)%.o))

#Compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE_FOLDER = -I $(INC_DIR)

#Rules
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE_FOLDER) -c $< -o $@

all: $(NAME)

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_FOLDER) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
