TARGET=main
OBJ=addressBook.o main.o

$(TARGET):$(OBJ)
	gcc $^ -o $@

addressBook.o:addressBook.c
	gcc -c $^ -o $@

main.o:main.c
	gcc -c $^ -o $@

clean:
	@rm -rf *.o $(TARGET)