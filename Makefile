# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 11:38:23 by jberay            #+#    #+#              #
#    Updated: 2024/01/18 08:07:51 by jberay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf

SRCS 			=	pipex.c \
					ft_split_pipex.c
	
OBJS			=	$(SRCS:%.c=%.o)

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

all:				$(NAME)

$(NAME):			$(LIBFT) $(OBJS)
					$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME) 
					
%.o:%.c
					$(CC) $(CFLAGS) -c $< -o $@		
							
$(LIBFT):
					make -C $(LIBFT_PATH) all

					

clean:
					make -C $(LIBFT_PATH) clean
					$(RM) $(OBJS)

fclean:				clean
					make -C $(LIBFT_PATH) fclean
					$(RM) $(NAME)
					

re:					fclean all

.PHONY:				all bonus clean fclean re libft