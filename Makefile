NAME	= program

all:
	make -C ./nm
	make -C ./objdump

objdump:
	make -C ./objdump

nm:
	make -C ./nm

clean:
	make -C ./objdump clean
	make -C ./nm clean

fclean: clean
	make -C ./objdump fclean
	make -C ./nm fclean

re: fclean all

.PHONY: all clean fclean re
