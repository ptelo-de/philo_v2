
NAME			=	philo
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g #-fsanitize=thread #-pthread
RM				=	rm -rf

INC_DIR			=	includes/
OBJ_DIR			=	objs/
SRC_DIR			=	srcs/

SRC				=	$(SRC_DIR)main.c \
					$(SRC_DIR)init.c \
					$(SRC_DIR)utils.c \
					$(SRC_DIR)routines.c \


OBJ				=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o) 

$(NAME):			$(OBJ)
					$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c | $(OBJ_DIR)
					$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

$(OBJ_DIR):
					mkdir -p $@

all:				$(NAME)

clean:
					if [ -d $(OBJ_DIR) ]; then $(RM) $(OBJ_DIR); fi

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
