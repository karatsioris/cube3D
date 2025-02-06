NAME    = cub3D

# Compiler
CC      = gcc
CFLAGS  = -Wextra -Wall -Werror -g3

# MLX library flags
MLXFLAGS = -lglfw -L /usr/local/lib

# Directories
SRC_DIR = src
OBJ_DIR = src/bin

# Source files for Cube3D
SRC = error_handling.c file_and_argv_valid.c \
	  map_boundary_val.c initialize_game.c \
	  memory_cleaning.c parsing_functions.c \
	  parsing_textures.c validate_map.c \
	  main.c memory.c parsing.c raycasting.c \
	  cleaning.c loading_texture.c cast_ray.c \
	  get_texture.c can_move.c cast_rays.c \

# Object files
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Libraries
LIB = src/libft/bin/libft.a
MLX42 = MLX42/build/libmlx42.a

# Build executable in the main project folder
$(NAME): $(MLX42) $(OBJ)
	@cd src/libft && make
	@$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(MLX42) $(OBJ) $(LIB)
	@echo "\033[0;37mCompilation of the Project OK!\033[0m"

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi
	@echo "Compiling $< -> $@"
	@$(CC) $(CFLAGS) -c $< -o $@ && echo "\033[0;35m$< OK!\033[0m" || echo "\033[0;31m$< KO!\033[0m"

# Build MLX42 library if not present
$(MLX42):
	@if [ ! -d MLX42/build ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd MLX42 && cmake -B build
	@cd MLX42 && cmake --build build -j4

# Build everything
all: $(MLX42) $(NAME)

# Clean MLX42
cleanmlx:
	@rm -rf MLX42
	@echo "MLX42 folder removed"

# Clean object files
clean:
	@cd src/libft && make clean
	@rm -rf $(OBJ_DIR)
	@echo "Objects removed"

# Remove objects and executable
fclean:
	@cd src/libft && make fclean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)
	@echo "Objects and executable removed"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re cleanmlx