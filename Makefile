NAME = minishell
LIBFT = libft/libft.a

# Directories
SRC_DIR = src/
CMD_DIR = commands/
UTLS_DIR = utils/
REDIR_DIR = redirections/
PARSING_DIR = parsing/
EXEC_DIR = exec/

SRCS =	$(SRC_DIR)ft_free_error.c \
		$(SRC_DIR)ft_init_lst.c \
		$(SRC_DIR)ft_splitou.c \
		$(SRC_DIR)main.c \
		$(SRC_DIR)init.c \
		$(CMD_DIR)commands.c \
		$(CMD_DIR)environnement.c \
		$(CMD_DIR)echo.c \
		$(CMD_DIR)pwd.c \
		$(CMD_DIR)cd.c \
		$(CMD_DIR)cd_2.c \
		$(CMD_DIR)export.c \
		$(CMD_DIR)export_2.c \
		$(CMD_DIR)unset.c \
		$(PARSING_DIR)handle_var.c \
		$(PARSING_DIR)handle_var_2.c \
		$(PARSING_DIR)handle_quotes.c \
		$(REDIR_DIR)redirection.c \
		$(REDIR_DIR)redirection_2.c \
		$(REDIR_DIR)redir_parsing.c \
		$(UTLS_DIR)utils.c \
		$(UTLS_DIR)utils_2.c \
		$(CMD_DIR)export_concat.c \
		$(EXEC_DIR)exec_pipeline.c \
		$(EXEC_DIR)parse_exec.c

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
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline -lhistory -lncurses

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
