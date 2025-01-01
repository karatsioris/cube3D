# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Library name
NAME = libft.a

# Build directory
OBJDIR = ../../bin/libft

# Source files for libft
SRCS = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_utoa_base.c \
	ft_printf.c ft_putunsignednbr_fd.c print_hex.c \
	get_next_line.c ft_strleni.c ft_realloc.c get_next_utils.c \

# Object files
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Rules
all: $(OBJDIR)/$(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ && echo "\033[0;32m$< OK!\033[0m" || echo "\033[0;31m$< KO!\033[0m"

$(OBJDIR)/$(NAME): $(OBJS)
	@ar rcs $@ $^

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(OBJDIR)/$(NAME)

re: fclean all

.PHONY: all clean fclean re