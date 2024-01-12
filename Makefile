#Compiler options
CC=gcc
CFLAGS= -Wall -pedantic -Iinc

#Linker options
LFLAGS = -lssl -lcrypto -lpthread

#Executable
TARGET = MD5craker

#Var
SRC = src/
INC = inc/
OBJ = obj/

$(TARGET): main.o user.o dict.o fdata.o password.o threads.o utility.o
	$(CC) $(CFLAGS) $(OBJ)main.o $(OBJ)user.o $(OBJ)dict.o \
			$(OBJ)fdata.o $(OBJ)password.o $(OBJ)threads.o \
			$(OBJ)utility.o $(LFLAGS) -o $(TARGET)

main.o: $(SRC)main.c
	mkdir obj && \
	$(CC) $(CFLAGS) -c $(SRC)main.c -o $(OBJ)main.o

user.o: $(SRC)user.c $(INC)user.h
	$(CC) $(CFLAGS) -c $(SRC)user.c -o $(OBJ)user.o

dict.o: $(SRC)dict.c $(INC)dict.h
	$(CC) $(CFLAGS) -c $(SRC)dict.c -o $(OBJ)dict.o

fdata.o: $(SRC)fdata.c $(INC)fdata.h
	$(CC) $(CFLAGS) -c $(SRC)fdata.c -o $(OBJ)fdata.o

password.o: $(SRC)password.c $(INC)password.h
	$(CC) $(CFLAGS) -c $(SRC)password.c -o $(OBJ)password.o

threads.o: $(SRC)threads.c $(INC)threads.h
	$(CC) $(CFLAGS) -c $(SRC)threads.c -o $(OBJ)threads.o

utility.o: $(SRC)utility.c $(INC)utility.h
	$(CC) $(CFLAGS) -c $(SRC)utility.c -o $(OBJ)utility.o

clean:
	rm -r $(OBJ) $(TARGET)