CC = g++
CFLAGS = -std=c++11

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = state_machine

.PHONY: all clean run

all: $(EXEC)

$(EXEC): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

.cpp.o:
	@$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	@./$(EXEC)

clean:
	@rm -f $(OBJS) $(EXEC) && clear
