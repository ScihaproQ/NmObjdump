NAMENM	=	my_nm
NAMEOBJ	=	my_objdump

SRCSOBJ	=	./objdump/main.c \
        ./objdump/dumps_32.c \
        ./objdump/dumps_64.c \
        ./objdump/prints.c \
        ./objdump/read_at_position.c \
        ./objdump/machines.c \

SRCSNM	=	./nm/main.c \

OBJSNM	=	$(SRCSNM:.c=.o)
OBJSOBJ	=	$(SRCSOBJ:.c=.o)

CFLAGS	=	-W -Wall -Wextra -I ./objdump -I ./nm

CC	=	gcc

all:		nm objdump

nm:		$(NAMENM)

objdump:	$(NAMEOBJ)

$(NAMENM):	$(OBJSNM)
		$(CC) -o $(NAMENM) $(SRCSNM)
$(NAMEOBJ):	$(OBJSOBJ)
		$(CC) -o $(NAMEOBJ) $(SRCSOBJ)

clean:
	rm -f $(OBJSNM)
	rm -f $(OBJSOBJ)

fclean: 	clean
	rm -f $(NAMENM)
	rm -f $(NAMEOBJ)

re: fclean all
