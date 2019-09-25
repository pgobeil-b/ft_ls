# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/08 19:46:52 by pgobeil-          #+#    #+#              #
#    Updated: 2019/09/24 22:13:24 by pgobeil-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_ls

SRC := parsing.c print.c formating.c btrees.c extra_functs.c

OBJDIR := objs

HEADER := -I libft

LIBFTDIR := ./libft

OBJS := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC := gcc

CFLAGS := -Wall -Werror -Wextra -c

.PHONY: all clean fclean re
.SUFFIXES: .c .o

all: $(NAME)

$(NAME): OBJS
	$(CC) $(OBJS) -o $(NAME) $(HEADER) -L $(LIBFTDIR) -lft
OBJS: LIB
		mkdir $(OBJDIR)
		$(CC) $(CFLAGS) $(SRC) $(HEADER)
		mv *.o $(OBJDIR)

LIB:
	make -C $(LIBFTDIR)
	rm -rf $(OBJDIR)

clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(OBJDIR)

fclean: clean
		make -C $(LIBFTDIR) fclean
		rm -f $(NAME)
