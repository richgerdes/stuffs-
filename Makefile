CC=gcc
CFLAGS=-g -Wall
DEPS = hashTable.h
OBJ = search.c hashTable.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

search: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
	
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ search $(INCDIR)/*~ 
