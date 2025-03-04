NAME	=	libft.a

FLAG	=	-Wall -Werror -Wextra

AR		=	ar -rsc

SRCS	=	string1.c string2.c

OBJS	=	$(SRCS:.c=.o)

all:	$(NAME)
		

%.o: 	%.c libft.h Makefile
		cc $(FLAG) $< -o $@ -c 

$(NAME): $(OBJS)
		$(AR) $(NAME) $(OBJS)

clean:
		@rm -f $(OBJS)

fclean:
		@rm -f $(OBJS) $(NAME)

re: 	clean all

.PHONY: all clean fclean re