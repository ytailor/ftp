# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytailor <ytailor@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/13 15:44:34 by ytailor           #+#    #+#              #
#    Updated: 2014/05/18 21:20:48 by ytailor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client

SERVEUR = serveur

FLAGS = -Wall -Wextra -Werror

SRCS_SERVEUR = ft_serveur.c ft_actions.c ft_actions2.c

SRCS_CLIENT = ft_client.c ft_get_put.c

OBJS_SERVEUR = $(SRCS_SERVEUR:.c=.o)

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

all : $(CLIENT) $(SERVEUR)

$(CLIENT): $(OBJS_CLIENT)
	make -C libft
	gcc $(FLAGS) $(SRCS_CLIENT) -o $(CLIENT) libft/libft.a

$(SERVEUR): $(OBJS_SERVEUR)
	make -C libft
	gcc $(FLAGS) $(SRCS_SERVEUR) -o $(SERVEUR) libft/libft.a

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_CLIENT)
	rm -f $(OBJS_SERVEUR)

fclean: clean
	make fclean -C libft/
	rm -f $(CLIENT)
	rm -f $(SERVEUR)

re: fclean all

.PHONY: all clean fclean re
