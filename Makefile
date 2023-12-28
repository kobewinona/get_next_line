NAME	= libgnl.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
SRCS 	= get_next_line.c get_next_line_utils.c
OBJS 	= $(SRCS:.c=.o)

$(NAME): $(OBJS) libgnl.h libgnl_internal.h
	$(AR) rcs $(NAME) $^

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJS)
	
fclean: clean
	$(RM) $(NAME)
	
re: fclean all

bonus: all