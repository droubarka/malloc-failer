
CC = cc
CFLAGS = -Wall -Wextra -Werror
TARGET = xmalloc

INC_FILES = xmalloc.h
SRC_FILES = xmalloc.c
OBJ_FILES = $(SRC_FILES:%.c=%.o)

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	ar crs $@ $?

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@ $(MACROS)

clean:
	@rm -v -rf $(OBJ_FILES)

fclean: clean
	@rm -v -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re
