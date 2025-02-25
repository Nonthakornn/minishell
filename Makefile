NAME = minishell
CC = cc 
CFLAGS =  -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
RM = rm -rf

SRC_FILES = main.c utils.c token_utils.c free.c linklist_token.c \
			linklist_pipe.c
OBJ_DIR = obj

OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all:			$(NAME)

$(OBJ_DIR):
				mkdir -p $(OBJ_DIR)

$(NAME):		$(OBJ_FILES)
				$(CC) $(CFLAGS) $(OBJ_FILES) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o:	%.c | $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJ_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
