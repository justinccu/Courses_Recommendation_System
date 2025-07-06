CC = gcc
CFLAGS = -Wall -Wextra

SRCS = main.c Person.c import.c
OBJS = $(SRCS:.c=.o)
DEPS = Person.h import.h

TARGET = test.out

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	rm -f $(OBJS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
