

NAME = minishell
LIBFT = libft/libft.a

# Sources
SRC_DIR = src/
SRCS =	$(SRC_DIR)ft_free_error.c \
		$(SRC_DIR)ft_init_lst.c \
		$(SRC_DIR)ft_splitou.c \
		$(SRC_DIR)minitest.c \
		$(SRC_DIR)utils.c \

# Objects
OBJS = $(SRCS:.c=.o)

# Headers
HEAD = header/push_swap.h

# Compiler and flags
CC = cc -g
CFLAGS = -Wall -Werror -Wextra

# Commands
RM = rm -f

# Rules
all: $(NAME)

# Compilation
$(NAME): $(OBJS) $(LIBFT)
	@printf "\rCompiling $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@printf "\r$(NAME) compiled successfully.\n"

# Compile libft
$(LIBFT):
	@printf "\rCompiling libft..."
	@make bonus -C libft/ --no-print-directory
	@printf "\rLibft compiled successfully.\n"

# Compilation des fichiers .o à partir des .c
%.o: %.c $(HEAD)
	@printf "\rCompiling $<...               "
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean objects
clean:
	@printf "\rCleaning object files..."
	@$(RM) $(OBJS)
	@make clean -C libft/ --no-print-directory
	@printf "\rObject files cleaned.\n"

# Clean everything
fclean: clean
	@printf "\rRemoving $(NAME)..."
	@$(RM) $(NAME)
	@make fclean -C libft/ --no-print-directory
	@printf "\r$(NAME) removed.\n"

# Recompile
re: fclean all

# Phony targets
.PHONY: all clean fclean re