#############################################################################
#                                   VARIABLES                               
#############################################################################

NAME       := minishell
LIBFT      := libft/libft.a
SRC_DIR    := sources/main
CMD_DIR    := sources/builtins
CMD_DIR_ENV := sources/builtins/env
CMD_DIR_CD := sources/builtins/cd
CMD_DIR_PWD := sources/builtins/pwd
CMD_DIR_ECHO := sources/builtins/echo
EXIT_DIR   := sources/exit
UTLS_DIR   := sources/utils
REDIR_DIR  := sources/redirections
PARSING_DIR:= sources/parse_var_quotes
SIGNALS_DIR:= sources/signals
EXEC_DIR   := sources/exec

# FILES
SRCS := \
  $(SRC_DIR)/ft_free_error.c \
  $(SRC_DIR)/ft_init_lst.c    \
  $(SRC_DIR)/ft_splitou.c     \
  $(SRC_DIR)/main.c           \
  $(SRC_DIR)/init.c           \
  $(CMD_DIR)/parse_builtins.c       \
  $(CMD_DIR_ECHO)/echo.c           \
  $(CMD_DIR_PWD)/pwd.c            \
  $(CMD_DIR_CD)/cd.c             \
  $(CMD_DIR_CD)/cd_2.c           \
  $(CMD_DIR_ENV)/environnement.c  \
  $(CMD_DIR_ENV)/export.c         \
  $(CMD_DIR_ENV)/export_parsing.c       \
  $(CMD_DIR_ENV)/export_concat.c  \
  $(CMD_DIR_ENV)/unset.c          \
  $(PARSING_DIR)/handle_var.c \
  $(PARSING_DIR)/handle_var_2.c \
  $(PARSING_DIR)/handle_quotes.c \
  $(REDIR_DIR)/redirection.c  \
  $(REDIR_DIR)/redirection_2.c \
  $(REDIR_DIR)/redirection_cmd.c \
  $(REDIR_DIR)/redir_parsing.c \
  $(EXIT_DIR)/exit.c \
  $(UTLS_DIR)/utils.c         \
  $(UTLS_DIR)/utils_2.c       \
  $(EXEC_DIR)/exec_pipeline.c \
  $(EXEC_DIR)/parse_exec.c \
  $(SIGNALS_DIR)/signal.c

# Objects
OBJS = $(SRCS:.c=.o)

# Headers
HEAD = header/push_swap.h

# Compiler and flags
CC = cc -Wall -Wextra -Werror -g #-g -fsanitize=address
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
    CFLAGS += -I/opt/homebrew/opt/readline/include
    LDFLAGS += -L/opt/homebrew/opt/readline/lib -lreadline -lhistory
else
    LDFLAGS += -lreadline -lhistory
endif

# Commands
RM = rm -f

# Rules
all: $(NAME)

# Compilation
$(NAME): $(OBJS) $(LIBFT)
	@printf "\rCompiling $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

	@printf "\r\033[0;32m$(NAME) compiled successfully.\n\033[0m"

# Compile libft
$(LIBFT):
	@printf "\rCompiling libft..."
	@make bonus -C libft/ --no-print-directory
	@printf "\r\033[0;32mLibft compiled successfully.\n\033[0m"

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