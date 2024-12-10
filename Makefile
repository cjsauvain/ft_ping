#Executable Name
NAME = ft_ping

#Directories
SRCS_DIR = srcs
OBJS_DIR = objects
INC_DIR  = include

#Sources / Headers
SRC	=	main.c					\
		ft_ping.c				\
		process_checksum.c		\

SRC_SENDING =	send_echo_request.c		\
				create_icmp_hdr.c		\
				create_socket.c			\

SRC_RECEIVING =	receive_echo_reply.c	\
				check_checksum_reply.c	\

SRC_PARSING =	parsing.c			\
				update_addr_list.c	\

SRC_SIGNAL =	handler.c	\

SRC_DISPLAY =	display_usage_message.c	\
				display_reply.c			\
				display_ping_stats.c	\
				display_data_sent.c		\

SRCS =	$(addprefix $(SRCS_DIR)/, $(SRC))						\
		$(addprefix $(SRCS_DIR)/sending/, $(SRC_SENDING))		\
		$(addprefix $(SRCS_DIR)/receiving/, $(SRC_RECEIVING))	\
		$(addprefix $(SRCS_DIR)/parsing/, $(SRC_PARSING))		\
		$(addprefix $(SRCS_DIR)/signal/, $(SRC_SIGNAL))			\
		$(addprefix $(SRCS_DIR)/display/, $(SRC_DISPLAY))		\

HEADERS = $(INC_DIR)/ft_ping.h

#Objects
OBJS = $(subst $(SRCS_DIR)/,,$(SRCS:%.c=$(OBJS_DIR)/%.o))

#Compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INC_FOLDER = -I $(INC_DIR)

#Rules
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INC_FOLDER) -c $< -o $@

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p	$(OBJS_DIR)/sending 	\
				$(OBJS_DIR)/receiving	\
				$(OBJS_DIR)/parsing		\
				$(OBJS_DIR)/signal		\
				$(OBJS_DIR)/display		\

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(OBJS) $(INC_FOLDER) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
