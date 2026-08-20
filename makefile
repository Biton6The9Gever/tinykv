CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -MMD -MP
TARGET = main

SRCS = main.c parser.c utils.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

.PHONY: all clean