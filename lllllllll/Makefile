# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/04 13:14:47 by daafonso          #+#    #+#              #
#    Updated: 2024/10/22 12:54:55 by daniel149af      ###   ########.fr        #
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
ft_striteri.c \
ft_strmapi.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_substr.c \
ft_strtrim.c \
ft_tolower.c \
ft_toupper.c

BONUS 		= ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
			ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
			ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

SRCSALL 	= 		${SRC} ${BONUS}

OBJS		=		$(SRC:.c=.o)

OBJSALL		=		${SRCSALL:.c=.o}

CC			= 		gcc
RM			= 		rm -f
CFLAGS		= 		-Wall -Wextra -Werror

NAME		=		libft.a


all:		$(NAME)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

bonus:		${OBJSALL}
			ar rcs $(NAME) $(OBJSALL)

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS) $(OBJSALL)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
