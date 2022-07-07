TARGET := fdf

CC := gcc
CFLAGS := -Wall -Wextra -Werror -g #-fsanitize
LDFLAGS := -Lmlx -lmlx -framework OpenGL -framework AppKit

BUILD_DIR := build
SRC_DIRS := src
SRCS := main.c draw_line.c
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

# The final build step.
$(TARGET): $(OBJS)
	make -C mlx
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.o: $(SRC_DIRS)/%.c
	@mkdir -p $(dir $@)
	$(CC) -Imlx $(CFLAGS) -c $< -o $@

.PHONY: clean fclean re

all: $(TARGET)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(TARGET)

re: fclean all
