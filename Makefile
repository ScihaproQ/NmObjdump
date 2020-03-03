NAME	= program

all:
	make -C ./nm
	make -C ./objdump
	mv  ./nm/my_nm ./
	mv  ./objdump/my_objdump ./

objdump:
	make -C ./objdump
	mv  ./objdump/my_objdump ./

nm:
	make -C ./nm
	mv  ./nm/my_nm ./

clean:
	make -C ./objdump clean
	make -C ./nm clean

fclean: clean
	make -C ./objdump fclean
	make -C ./nm fclean

re: fclean all

.PHONY: all clean fclean re
