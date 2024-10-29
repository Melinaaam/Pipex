NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRCDIR = srcs
OBJDIR = obj
LIBFT_DIR = libft
LIBFT = -L$(LIBFT_DIR) -lft

SRCS = $(SRCDIR)/utils.c \
	$(SRCDIR)/pipex.c
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

BONUSDIR = bonus
BONUSOBJDIR = obj_bonus
BONUS = $(BONUSDIR)/pipex_bonus.c \
	$(BONUSDIR)/utils_bonus.c
OBJS_BONUS = $(SRCS_BONUS:$(BONUSDIR)/%.c=$(BONUSOBJDIR)/%.o)

PINK = \033[38;5;213m
BLUE = \033[38;5;75m
RESET = \033[0m
BOLD := \033[1m

INCLUDES = -Iincludes -I$(LIBFT_DIR)/includes

all: $(NAME)

$(NAME): $(LIBFT_DIR)/libft.a $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(BOLD)$(PINK)🎉 Compile with success !!! 🎉$(RESET)"
bonus: $(NAME_BONUS)

# Build the bonus executable
$(NAME_BONUS): $(LIBFT_DIR)/libft.a $(BONUSOBJDIR) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)
	@echo "$(BOLD)$(BLUE)🎉 Bonus compiled with success !!! 🎉$(RESET)"

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BONUSOBJDIR):
	mkdir -p $(BONUSOBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BONUSOBJDIR)/%.o: $(BONUSDIR)/%.c | $(BONUSOBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BONUSOBJDIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@echo "🧹 Clean Over ! 🧹"

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make -C $(LIBFT_DIR) fclean
	@echo "🧼 All Clean Over !!! 🧼"

re: fclean all

.PHONY: all clean fclean re libft bonus
