# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 12:31:40 by carlos-m          #+#    #+#              #
#    Updated: 2024/03/22 12:31:42 by carlos-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

SRC = philosophers.c parse.c

OBJ = $(SRC:.c=.o)

CFLAGS := -Wall -Werror -Wextra

REMOVE = rm -rf

CC = cc

all: $(NAME)

$(NAME) : $(OBJ)
		$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	$(REMOVE) $(OBJ)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

.PHONY: all clean fclean re