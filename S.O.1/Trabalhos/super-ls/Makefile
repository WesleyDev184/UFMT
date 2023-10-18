CC = gcc
CFLAGS = -Wall -g
SRC = main.c   # Substitua com a lista de seus arquivos de origem
TARGET = teste # Substitua pelo nome do seu executável

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC)

.PHONY: clean

clean:
	rm -f $(TARGET) & clear