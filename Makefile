#Executable Name
NAME = ft_ping

#Directories
SRCS_DIR = srcs
OBJS_DIR = objects
INC_DIR  = include

#Sources / Headers
SRC	=	main.c			\
		ft_ping.c		\
		run_ping.c		\
		clean_exit.c	\

SRC_SENDING =	send_echo_request.c		\
				create_icmp_hdr.c		\

SRC_RECEIVING =	receive_echo_reply.c	\
				check_checksum_reply.c	\
				process_reply.c			\

SRC_SOCKETS =	create_sockets.c		\
				set_sock_opt.c			\
				close_sockets.c			\

SRC_UTILS =		process_checksum.c		\
				get_addr_struct.c		\
				get_source_addr.c	\

SRC_PARSING =	parsing.c					\
				initialize_ping_struct.c	\

SRC_SIGNAL =	signal.c	\

SRC_TERMIOS =	termios_config.c	\

SRC_DISPLAY =	display_usage_message.c	\
				display_reply.c			\
				display_ping_stats.c	\
				display_data_sent.c		\
				display_icmp_message.c	\
				display_original_pckt.c	\
				display_sig.c			\

SRC_ICMP_MESSAGES =	get_destination_unreachable_message.c 	\
					get_source_quench_message.c				\
					get_parameter_problem_message.c			\
					get_time_exceeded_message.c				\
					get_redirect_message.c					\

SRC_TIMESTAMPS =	update_timestamps.c	\
					get_time_ms.c		\

SRCS =	$(addprefix $(SRCS_DIR)/, $(SRC))								\
		$(addprefix $(SRCS_DIR)/sending/, $(SRC_SENDING))				\
		$(addprefix $(SRCS_DIR)/receiving/, $(SRC_RECEIVING))			\
		$(addprefix $(SRCS_DIR)/sockets/, $(SRC_SOCKETS))				\
		$(addprefix $(SRCS_DIR)/utils/, $(SRC_UTILS))					\
		$(addprefix $(SRCS_DIR)/parsing/, $(SRC_PARSING))				\
		$(addprefix $(SRCS_DIR)/signal/, $(SRC_SIGNAL))					\
		$(addprefix $(SRCS_DIR)/termios/, $(SRC_TERMIOS))				\
		$(addprefix $(SRCS_DIR)/display/, $(SRC_DISPLAY))				\
		$(addprefix $(SRCS_DIR)/icmp_messages/, $(SRC_ICMP_MESSAGES))	\
		$(addprefix $(SRCS_DIR)/timestamps/, $(SRC_TIMESTAMPS))			\

HEADER = $(INC_DIR)/ft_ping.h

#Objects
OBJS = $(subst $(SRCS_DIR)/,,$(SRCS:%.c=$(OBJS_DIR)/%.o))

#Compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LIBINC = -lm
INC_FOLDER = -I $(INC_DIR)

#Rules
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) $(INC_FOLDER) -c $< -o $@

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p	$(OBJS_DIR)/sending 		\
				$(OBJS_DIR)/receiving		\
				$(OBJS_DIR)/sockets			\
				$(OBJS_DIR)/utils			\
				$(OBJS_DIR)/parsing			\
				$(OBJS_DIR)/signal			\
				$(OBJS_DIR)/display			\
				$(OBJS_DIR)/icmp_messages	\
				$(OBJS_DIR)/timestamps		\
				$(OBJS_DIR)/termios			\

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INC_FOLDER) -o $(NAME) $(LIBINC)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
