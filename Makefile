NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRCDIR = srcs
OBJDIR = obj
LIBFT_DIR = libft
LIBFT = -L$(LIBFT_DIR) -lft

SRCS = $(SRCDIR)/utils.c $(SRCDIR)/pipex.c
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

BONUSDIR = bonus
BONUSOBJDIR = obj_bonus
BONUS_SRCS = $(BONUSDIR)/pipex_bonus.c $(BONUSDIR)/utils_bonus.c
OBJS_BONUS = $(BONUS_SRCS:$(BONUSDIR)/%.c=$(BONUSOBJDIR)/%.o)

$(info BONUS_SRCS = $(BONUS_SRCS))
$(info OBJS_BONUS = $(OBJS_BONUS))

PINK = \033[38;5;213m
BLUE = \033[38;5;75m
RESET = \033[0m
BOLD := \033[1m

INCLUDES = -Iincludes -I$(LIBFT_DIR)/includes

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(BOLD)$(PINK)🎉 Compile with success !!! 🎉$(RESET)"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)
	@echo "$(BOLD)$(BLUE)🎉 Bonus compiled with success !!! 🎉$(RESET)"

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BONUSOBJDIR)/%.o: $(BONUSDIR)/%.c
	@mkdir -p $(BONUSOBJDIR)
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
