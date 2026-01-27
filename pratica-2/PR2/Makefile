# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -g
TARGET = exe

# Arquivos objeto
OBJS = pratica.o main.o

# Alvo principal
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para aluno.o
pratica.o: pratica.c pratica.h
	$(CC) $(CFLAGS) -c pratica.c

# Regra para pratica.o
main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

# Limpeza
clean:
	rm -f $(OBJS) $(TARGET)

# Limpeza completa
purge: clean
	rm -f output.out

.PHONY: clean purge