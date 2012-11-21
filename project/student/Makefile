main:main.o add.o  menu.o print_list.o delete.o read_info.o save.o
	gcc main.o add.o  menu.o print_list.o delete.o read_info.o save.o -o main
main.o:main.c linkedlist.h 
	gcc -c main.c
add.o:add.c linkedlist.h
	gcc -c add.c
menu.o:menu.c linkedlist.h
	gcc -c menu.c
print_list.o:print_list.c linkedlist.h
	gcc -c print_list.c
delete.o:delete.c linkedlist.h
	gcc -c delete.c
read_info.o:read_info.c linkedlist.h
	gcc -c read_info.c	
save.o:save.c linkedlist.h
	gcc -c save.c
clean:
	rm *.o main
