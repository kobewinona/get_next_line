MACHINE		:= $(shell uname -m)
NAME		= libgnl-$(MACHINE).a

OBJS_DIR	= ./obj

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
SRCS 		= get_next_line.c get_next_line_utils.c
OBJS 		= $(SRCS:%.c=$(OBJS_DIR)/%.o)

$(NAME): $(OBJS) libgnl_internal.h libgnl.h
	$(AR) rcs $(NAME) $^

all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJS_DIR)
	
fclean: clean
	$(RM) $(NAME)
	
re: fclean all

bonus: all