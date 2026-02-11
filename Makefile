CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lreadline
# Added flag for command recall if code does not work try installing:
# sudo apt-get update && sudo apt-get install libreadline-dev


TARGET = mysh
SRCS = mysh.c parser.c interpreter.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c header.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)