NAME = minishell
LIB_PATH = lib
SRC_DIR = srcs
BUILD_DIR = obj

SRC_FILES = main.c token_utils.c free_close.c linklist_redirect.c \
			linklist_process.c exec_heredoc.c redirect.c  \
			split_pipe.c exec_process.c exec_processes.c get_path.c linklist_token.c \
			lexical.c lexical2.c syntax.c syntax2.c free_return.c \
			error_exec.c error_export.c error_option.c \
			process_variable.c get_process_variable.c \
			exec_env.c exec_unset.c exec_export.c exec_export_add.c \
			exec_pwd.c exec_cd.c exec_chdir.c

HEADERS = srcs/minishell.h

INCLUDES = -I $(LIB_PATH) -I$(SRC_DIR)

LIBS = -L$(LIB_PATH) -lft

OBJS = $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

CC = cc 
CFLAGS =  -Wall -Wextra -Werror -g
# CFLAGS =  -Wall -g
RM = rm -rf
LDFLAGS = -lreadline
VALGRIND = valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all \
			--suppressions=readline.supp

all:			$(NAME)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) Makefile
				@mkdir -p $(BUILD_DIR)
				@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(NAME):		$(OBJS)
				@$(MAKE) -C $(LIB_PATH)
				@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)

vg:				$(NAME)
				$(VALGRIND) ./$(NAME)

clean:
				@$(MAKE) -C $(LIB_PATH) clean
				@$(RM) $(BUILD_DIR)

fclean:			clean
				@$(MAKE) -C $(LIB_PATH) fclean
				@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
