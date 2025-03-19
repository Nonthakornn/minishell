NAME	=	libft.a

FLAG	=	-Wall -Werror -Wextra

AR		=	ar -rsc

SRCS	=	num_itoa.c num_utils.c \
			str_array_remove.c str_array_add.c str_array_utils.c str_array_sort.c \
			str_join.c str_print.c str_split.c str_validate.c str_utils.c 

OBJS	=	$(SRCS:.c=.o)

all:	$(NAME)

%.o: 	%.c libft.h Makefile
		@cc $(FLAG) $< -o $@ -c 

$(NAME): $(OBJS)
		@$(AR) $(NAME) $(OBJS)

clean:
		@rm -f $(OBJS)

fclean:
		@rm -f $(OBJS) $(NAME)

re: 	clean all

.PHONY: all clean fclean re