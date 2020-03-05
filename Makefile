NAMENM	=	my_nm
NAMEOBJ	=	my_objdump

SRCOBJ	=	./objdump/main.c \
        ./objdump/dumps_32.c \
        ./objdump/dumps_64.c \
        ./objdump/prints.c \
        ./objdump/read_at_position.c \
        ./objdump/machines.c \

SRCNM	=	./nm/main.c

OBJSNM	=	$(SRCSNM:.c=.o)
OBJSOBJ	=	$(SRCSOBJ:.c=.o)

CFLAGS	=	-W -Wall -Wextra -Werror -I ./objdump

CC	=	gcc

all:		nm objdump

nm:		$(NAMENM)

objdump:	$(NAMEOBJ);

$(NAMENM):	$(OBJSNM)
		$(CC) -o $(NAMENM) $(SRCNM)
$(NAMEOBJ):	$(OBJSOBJ)
		$(CC) -o $(NAMEOBJ) $(SRCOBJ)

clean:
	rm -f $(OBJSNM)
	rm -f $(OBJSOBJ)

fclean: 	clean
	rm -f $(NAMENM)
	rm -f $(NAMEOBJ)

.PHONY: all clean fclean re
