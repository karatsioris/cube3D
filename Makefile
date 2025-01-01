CC         := cc
CFLAGS     := -Wall -Wextra -Werror -g -arch arm64
CFLAGS_MLX := -Wextra -Wall -Werror -Wunreachable-code -Ofast

SRCDIR     := ./src
OBJDIR     := $(SRCDIR)/bin

LIBFTNAME  := $(SRCDIR)/libft/bin/libft.a
LIBFTDIR   := $(SRCDIR)/libft

LIBMLX     := ./lib/MLX42
LIBMLXA    := $(LIBMLX)/build/libmlx42.a
LIB_MLX    := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

HEADERS    := -I $(SRCDIR) -I $(LIBMLX)/include -I $(LIBFTDIR)

SRCS       := $(SRCDIR)/error_handling.c $(SRCDIR)/file_and_argv_valid.c \
			  $(SRCDIR)/finding_direction.c $(SRCDIR)/map_boundary.c \
			  $(SRCDIR)/memory_cleaning.c $(SRCDIR)/parsing_functions.c \
			  $(SRCDIR)/parsing_textures.c $(SRCDIR)/validate_map.c \
			  $(SRCDIR)/main.c

OBJS       := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

NAME       := $(OBJDIR)/cub3D

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "\033[0;32mCompiled: $<\033[0m"

$(LIBMLXA): $(LIBFTNAME)
	@echo "\033[0;34m[DEBUG] Starting MLX42 build...\033[0m"
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@echo "\033[0;32m[DEBUG] MLX42 Built Successfully!\033[0m"

$(LIBFTNAME): $(wildcard $(LIBFTDIR)/*.c) | $(LIBFTDIR)/bin
	@echo "\033[0;34m[DEBUG] Checking if libft.a exists...\033[0m"
	@if [ ! -f "$(LIBFTNAME)" ]; then \
		echo "\033[0;33m[DEBUG] libft.a not found, building libft...\033[0m"; \
		make -C $(LIBFTDIR) --no-print-directory; \
		echo "\033[0;32m[DEBUG] libft.a built successfully!\033[0m"; \
	else \
		echo "\033[0;34m[DEBUG] libft.a already exists, skipping build.\033[0m"; \
	fi

$(LIBFTDIR)/bin:
	@mkdir -p $(LIBFTDIR)/bin
	@echo "\033[0;34m[DEBUG] Ensured libft/bin directory exists.\033[0m"


FORCE:

all: init-submodules $(LIBFTNAME) $(LIBMLXA) $(NAME)

debug-start:
	@echo "\033[0;34m[DEBUG] Starting Build Process...\033[0m"

debug-end:
	@echo "\033[0;32m[DEBUG] Build Process Completed!\033[0m"

init-submodules:
	@if [ -z "$(shell ls -A $(LIBMLX))" ]; then \
		git submodule init $(LIBMLX); \
		git submodule update $(LIBMLX); \
	fi

$(NAME): $(OBJS) $(LIBFTNAME)
	@echo "\033[0;34mLinking cub3D...\033[0m"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_MLX) -L$(SRCDIR)/libft/bin -lft $(HEADERS)
	@echo "\033[0;32m$(NAME) built successfully!\033[0m"

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFTDIR) clean --no-print-directory
	@rm -rf $(LIBMLX)/build
	@echo "\033[0;33mCleaned object files and MLX build artifacts.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean --no-print-directory
	@rm -rf $(OBJDIR)
	@rm -rf $(SRCDIR)/libft/bin
	@echo "\033[0;31mRemoved src/bin and libft/bin directories.\033[0m"

re: fclean all

.PHONY: all clean fclean re init-submodules FORCE

