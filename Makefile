# CC         := gcc # for some reason compile with gcc and not with cc

# ARCH := $(shell uname -m)
# ifeq ($(ARCH),arm64)
#     CFLAGS := -Wall -Wextra -Werror -g -arch arm64
# else
#     CFLAGS := -Wall -Wextra -Werror -g -arch x86_64
# endif

# # CFLAGS     := -Wall -Wextra -Werror -g -arch arm64
# CFLAGS_MLX := -Wextra -Wall -Werror -Wunreachable-code -Ofast

# SRCDIR     := ./src
# OBJDIR     := $(SRCDIR)/bin

# LIBFTNAME  := $(SRCDIR)/libft/bin/libft.a
# LIBFTDIR   := $(SRCDIR)/libft

# LIBMLX     := ./lib/MLX42
# LIBMLXA    := $(LIBMLX)/build/libmlx42.a
# LIB_MLX    := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# HEADERS    := -I $(SRCDIR) -I $(LIBMLX)/include -I $(LIBFTDIR)

# SRCS       := $(SRCDIR)/error_handling.c $(SRCDIR)/file_and_argv_valid.c \
# 			  $(SRCDIR)/finding_direction.c $(SRCDIR)/map_boundary_val.c \
# 			  $(SRCDIR)/memory_cleaning.c $(SRCDIR)/parsing_functions.c \
# 			  $(SRCDIR)/parsing_textures.c $(SRCDIR)/validate_map.c \
# 			  $(SRCDIR)/main.c

# OBJS       := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# NAME       := ./cube3D

# $(OBJDIR)/%.o: $(SRCDIR)/%.c
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
# 	@echo "\033[0;32m[DEBUG] Compiled: $<\033[0m"


# $(LIBMLXA): $(LIBFTNAME)
# 	@echo "\033[0;34m[DEBUG] Starting MLX42 build...\033[0m"
# 	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
# 	@echo "\033[0;32m[DEBUG] MLX42 Built Successfully!\033[0m"

# # Build Libft
# $(LIBFTNAME): $(wildcard $(LIBFTDIR)/*.c) | $(LIBFTDIR)/bin
# 	@echo "\033[0;34m[DEBUG] Checking if libft.a exists...\033[0m"
# 	@if [ ! -f "$(LIBFTNAME)" ]; then \
# 		echo "\033[0;33m[DEBUG] libft.a not found, building libft...\033[0m"; \
# 		make -C $(LIBFTDIR) --no-print-directory; \
# 		echo "\033[0;32m[DEBUG] libft.a built successfully!\033[0m"; \
# 	else \
# 		echo "\033[0;34m[DEBUG] libft.a already exists, skipping build.\033[0m"; \
# 	fi

# # Ensure libft/bin Directory Exists
# $(LIBFTDIR)/bin:
# 	@mkdir -p $(LIBFTDIR)/bin
# 	@echo "\033[0;34m[DEBUG] Ensured libft/bin directory exists.\033[0m"

# # Build Main Target
# all: debug-start init-submodules $(LIBFTNAME) $(LIBMLXA) $(NAME) debug-end

# debug-start:
# 	@echo "\033[0;34m[DEBUG] Starting Build Process...\033[0m"

# debug-end:
# 	@echo "\033[0;32m[DEBUG] Build Process Completed!\033[0m"

# # Link Final Binary
# $(NAME): $(OBJS) $(LIBFTNAME)
# 	@echo "\033[0;34m[DEBUG] Linking cub3D in the main folder...\033[0m"
# 	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_MLX) -L$(LIBFTDIR)/bin -lft $(HEADERS)
# 	@echo "\033[0;32m[DEBUG] cub3D built successfully in the main folder!\033[0m"

# # Initialize Submodules
# init-submodules:
# 	@if [ -z "$(shell ls -A $(LIBMLX))" ]; then \
# 		git submodule init $(LIBMLX); \
# 		git submodule update $(LIBMLX); \
# 	fi

# # Clean Object Files
# clean:
# 	@rm -f $(OBJS)
# 	@make -C $(LIBFTDIR) clean --no-print-directory
# 	@rm -rf $(LIBMLX)/build
# 	@echo "\033[0;33m[DEBUG] Cleaned object files and MLX build artifacts.\033[0m"

# # Full Cleanup
# fclean: clean
# 	@rm -f $(NAME)
# 	@make -C $(LIBFTDIR) fclean --no-print-directory
# 	@rm -rf $(OBJDIR)
# 	@rm -rf $(LIBFTDIR)/bin
# 	@echo "\033[0;31m[DEBUG] Removed cub3D binary, src/bin, and libft/bin directories.\033[0m"

# # Rebuild Everything
# re: fclean all

# .PHONY: all clean fclean re init-submodules debug-start debug-end



NAME	= cube3D
# Compiler
CC		= gcc
CFLAGS	= -Wextra -Wall -Werror
# MLXFLAGS = -lglfw -L "$(HOME)/.brew/opt/glfw/lib/"
MLXFLAGS = -lglfw -L /usr/local/lib

SRC_DIR = src
OBJ_DIR = src/bin

# Source files for Cube3d
SRC = main2.c

# Object files
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIB = src/libft/bin/libft.a

MLX42 = MLX42/build/libmlx42.a

$(OBJ_DIR)/$(NAME) : $(MLX42) $(OBJ)
	@cd src/libft && make
	@$(CC) $(CFLAGS) $(MLXFLAGS) -o $(OBJ_DIR)/$(NAME) $(MLX42) $(OBJ) $(LIB)
	@echo "\033[0;37mCompilation of the Project OK!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ && echo "\033[0;35m$< OK!\033[0m" || echo "\033[0;31m$< KO!\033[0m"

# $(OBJ_DIR)/$(NAME): $(OBJ)
# 	@ar rcs $@ $^

$(MLX42) :
	@if [ ! -d MLX42/build ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd MLX42 && cmake -B build
	@cd MLX42 && cmake --build build -j4

all : $(MLX42) $(OBJ_DIR)/$(NAME) $(OBJ)

cleanmlx :
	@rm -rf MLX42
	@echo "MLX42 folder removed"

clean :
	@cd src/libft && make clean
	@rm -rf $(OBJ)
	@echo "Objects removed"

fclean : 
	@cd src/libft && make fclean
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_DIR)/$(NAME)
	@echo "Objects and executable removed"

re : fclean all

.PHONY : all clean fclean re cleanall cleanmlx