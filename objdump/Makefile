NAME	= my_objdump

CC	= gcc

RM	= rm -f

SRCS	= ./main.c \
        ./dumps.c \
        ./prints.c \
        ./read_at_position.c \
        ./machines.c \

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./
CFLAGS += -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	 mv ./$(NAME) ../

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
