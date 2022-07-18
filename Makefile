TARGET := fdf

CC := gcc
CFLAGS := -Wall -Wextra -Werror -g#-fsanitize
MLXFLAGS := -Lmlx -lmlx -framework OpenGL -framework AppKit

LIBFT_DIR := libft/
LIBFT := libft/libft.a
MLX_DIR := mlx/
MLX := mlx/libmlx.a

BUILD_DIR := build
SRC_DIR := src
SRCS := main.c draw.c draw_line.c matrix.c read_map.c
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

# The final build step.
$(TARGET): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) -o $@ $(LIBFT) $(MLX)

# Build step for C source
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -Imlx $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

.PHONY: clean fclean re

all: $(TARGET)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(TARGET)

re: fclean all
