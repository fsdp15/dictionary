objects = main.o dicionario.o

programa: $(objects)
	gcc -o dicionario $(objects)

main.o:
	gcc -c main.c

dicionario.o:
	gcc -c dicionario.c $(flags)

dicionario.h.gch:
	gcc -c dicionario.h $(flags)

clean:
	rm $(objects)