main: tp.c main.c
	gcc tp.c main.c -o main
clean:
	rm -rf *.o
mrproper: clean
	rm -rf main
