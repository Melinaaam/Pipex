NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRCDIR = srcs
OBJDIR = obj
LIBFT_DIR = libft
LIBFT = -L$(LIBFT_DIR) -lft

SRCS = $(SRCDIR)/main.c \
	$(SRCDIR)/pipex.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

PINK = \033[38;5;213m
BLUE = \033[38;5;75m
RESET = \033[0m

BOLD := \033[1m

INCLUDES = -Iincludes -I$(LIBFT_DIR)/includes

all: $(NAME)

$(NAME): $(LIBFT_DIR)/libft.a $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(BOLD)$(PINK)🎉 Compile with success !!! 🎉$(RESET)"

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@echo "🧹 Clean Over ! 🧹"

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	@echo "🧼 All Clean Over !!! 🧼"

re: fclean all

.PHONY: all clean fclean re libft bonus
