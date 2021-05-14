# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmullan <tmullan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/15 13:01:13 by tmullan       #+#    #+#                  #
#    Updated: 2021/05/13 11:57:02 by zenotan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = ghostshell

ERR = error/error.c \
		error/err_msg.c

UTIL = struct_utils.c \
		dlist.c \
		lst_utils.c \
		history_utils.c \
		tur_utils.c

PAR = parser.c \
		parser_utils.c \
		handle_env.c \
		read_input.c \
		lexer.c

SHEL = shell_exec.c \
		prog_launch.c \
		redirect.c \
		pipe_exec.c

TEST = test.c

PAR_PREFIX = $(addprefix parser/, $(PAR))

UTIL_PREFIX = $(addprefix utils/, $(UTIL))

SHELL_PREFIX = $(addprefix shell_exec/, $(SHEL))

SRC = main.c \
		$(GNL) \
		$(ERR) \
		$(LEX_PREFIX) \
		$(PAR_PREFIX) \
		$(UTIL_PREFIX) \
		$(SHELL_PREFIX) \
		debug/printlists.c \
		# $(TEST) \
		# $(LFT_PREFIX)

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc
# CC = clang++

INCLUDES = -Iincludes

# REINS = -Ireins_termcap/incl -Ireins_termcap/lib/vector/incl

LIBFT = -Ilft/ -Ignl/

LEAKS = -fsanitize=leak

# TAIL	=	-Lreins_termcap/lib/vector/ -lvector -ltermcap

all: $(NAME)

$(NAME): $(OBJ)
		@make -C gnl/
		@make bonus -C lft/
		@$(CC) $(FLAGS) $(OBJ)  $(INCLUDES) $(LIBFT) -lft -Llft -lgnl -Lgnl -g -o $(NAME)

%.o: %.c
		$(CC) $(FLAGS) $(INCLUDES) $(REINS) $(LIBFT) -g -c $< -o $@

clean:
		@make clean -C gnl/
		@make clean -C lft/
		rm -f $(OBJ)

fclean: clean
		@make fclean -C gnl/
		@make fclean -C lft/
		rm -f $(NAME)

re: fclean all
