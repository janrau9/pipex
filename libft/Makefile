# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 09:33:34 by jberay            #+#    #+#              #
#    Updated: 2024/01/15 13:24:14 by jberay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_isalpha.c \
	  ft_isalnum.c \
	 ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_memset.c \
	ft_bzero.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	get_next_line.c

BONUS_SRC = ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c

OBJS := $(SRCS:.c=.o)

BONUS_OBJS := $(BONUS_SRC:.c=.o)

LIBH = libft.h

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

LIBC = ar -rcs

RM = rm -f

%.o: %.c $(LIBH) 
	@cc $(CFLAGS) -c $< -o $@  -I $(LIBH)

$(NAME): $(OBJS) 
	@$(LIBC) $(NAME) $(OBJS) 

bonus: .bonus

.bonus: $(BONUS_OBJS)
	@ar -rus $(NAME) $(BONUS_OBJS)
	@touch .bonus

all: $(NAME)

clean: 
	$(RM) $(OBJS) $(BONUS_OBJS) .bonus

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
