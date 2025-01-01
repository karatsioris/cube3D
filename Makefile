CC         := cc
CFLAGS     := -Wall -Wextra -Werror -g -arch arm64
CFLAGS_MLX := -Wextra -Wall -Werror -Wunreachable-code -Ofast

NAME       := cub3D
SRCDIR     := ./src
OBJDIR     := ./bin

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

OBJS       := $(SRCS:%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "\033[0;32mCompiled: $<\033[0m"

$(LIBMLXA):
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@echo "\033[0;34mMLX42 Built Successfully\033[0m"

$(LIBFTNAME):
	@echo "\033[0;33mBuilding libft...\033[0m"
	@make -C $(LIBFTDIR) --no-print-directory
	@echo "\033[0;32mlibft.a built successfully!\033[0m"

all: init-submodules $(LIBFTNAME) $(LIBMLXA) $(NAME)

init-submodules:
	@if [ -z "$(shell ls -A $(LIBMLX))" ]; then \
		git submodule init $(LIBMLX); \
		git submodule update $(LIBMLX); \
	fi

$(NAME): $(OBJS) $(LIBFTNAME)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_MLX) -L$(SRCDIR)/libft/bin -lft $(HEADERS)
	@echo "\033[0;32m$(NAME) built successfully!\033[0m"


clean:
	@rm -f $(OBJS)
	@make -C $(LIBFTDIR) clean --no-print-directory
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean --no-print-directory
	@rm -rf $(SRCDIR)/libft/bin

re: fclean all

.PHONY: all clean fclean re init-submodules
