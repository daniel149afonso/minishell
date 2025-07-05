# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/04 13:14:47 by daafonso          #+#    #+#              #
#    Updated: 2025/07/05 09:03:00 by bullestico       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memchr.c	\
ft_memmove.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memset.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_strndup.c \
ft_striteri.c \
ft_strmapi.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strcmp.c \
ft_strncmp.c \
ft_strndup.c \
ft_strnstr.c \
ft_strrchr.c \
ft_substr.c \
ft_strtrim.c \
ft_tolower.c \
ft_toupper.c

BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
		ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

SRCSALL 	= ${SRC} ${BONUS}
OBJS		= ${SRC:.c=.o}
OBJSALL		= ${SRCSALL:.c=.o}

CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror

NAME		= libft.a

# Build all
all: $(NAME)

$(NAME): $(OBJS)
	@printf "\rCreating $(NAME)..."
	@ar rcs $(NAME) $(OBJS)
	@printf "\r$(NAME) created successfully.\n"

# Bonus rule
bonus: ${OBJSALL}
	@printf "\rBuilding bonus into $(NAME)..."
	@ar rcs $(NAME) ${OBJSALL}
	@printf "\rLIBFT Bonus objects added successfully.\n"

# Compile .c into .o
%.o: %.c
	@printf "\rCompiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@printf "\rCleaning object files..."
	@$(RM) $(OBJS) $(OBJSALL)
	@printf "\rLIBFT object files cleaned.\n"

# Clean all
fclean: clean
	@printf "\rRemoving $(NAME)..."
	@$(RM) $(NAME)
	@printf "\rLIBFT removed.\n"

# Full rebuild
re: fclean all

.PHONY: all clean fclean re bonus
