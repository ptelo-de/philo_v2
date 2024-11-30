
CC = gcc
# CFLAGS = -Wall -Wextra -Werror -pthread -g
# CFLAGS_TREADS = -fsanitize=thread
# CFLAGS_ADDRESS = -fsanitize=address
SRC = $(wildcard srcs/*.c)
OBJ = $(SRC:.c=.o)
NAME = philosophers

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -Iinclude/ $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude/ -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	valgrind --tool=helgrind --log-file=helgrind_output.txt ./$(NAME) 2 800 200 200 10

.PHONY: all clean fclean re


























# NAME			=	philo
# CC				=	cc
# CFLAGS			=	-Wall -Wextra -Werror -g -fsanitize=thread #-pthread
# RM				=	rm -rf

# INC_DIR			=	includes/
# OBJ_DIR			=	objs/
# SRC_DIR			=	srcs/

# SRC				=	$(SRC_DIR)main.c \
# 					$(SRC_DIR)init.c \
# 					$(SRC_DIR)utils.c \
# 					$(SRC_DIR)routines.c \


# OBJ				=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o) 

# $(NAME):			$(OBJ)
# 					$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR)

# $(OBJ_DIR)%.o:		$(SRC_DIR)%.c | $(OBJ_DIR)
# 					$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

# $(OBJ_DIR):
# 					mkdir -p $@

# all:				$(NAME)

# clean:
# 					if [ -d $(OBJ_DIR) ]; then $(RM) $(OBJ_DIR); fi

# fclean:				clean
# 					$(RM) $(NAME)

# re:					fclean all

# .PHONY:				all clean fclean re
