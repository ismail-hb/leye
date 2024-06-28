# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 20:12:27 by jgrimaud          #+#    #+#              #
#    Updated: 2023/12/17 06:46:29 by jgrimaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



# ----------------------------------- NOTES ------------------------------------

# *.c							== *.c
# $(wildcard *.c)				== a.c b.c
# $(filter-out a c, a b c d)	== b d
# SRC = a.c b.c
# $(SRC:%.c=obj/%.o)			== obj/a.o obj/b.o

# |  : order-only-prerequisites (https://stackoverflow.com/a/38525905).
# $@ : target
# $< : 1st dependance
# $^ : all dependance



# ----------------------------------- PARAMS -----------------------------------

NAME	=	libft.a

INC_DIR	=	.
SRC_DIR	=	.
OBJ_DIR	=	obj

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

INC		=	libft.h
SRC		=	$(addprefix $(SRC_DIR)/, \
				ft_alloc.c			\
				ft_arr.c			\
				ft_char.c			\
				ft_char2.c			\
				ft_check.c			\
				ft_conv.c			\
				ft_error.c			\
				ft_exit.c			\
				ft_fd.c				\
				ft_free.c			\
				ft_gc.c				\
				ft_lst_iter.c		\
				ft_lst_read.c		\
				ft_lst_write.c		\
				ft_lst_write2.c		\
				ft_math.c			\
				ft_mem_read.c		\
				ft_mem_write.c		\
				ft_str_alloc.c		\
				ft_str_alloc2.c		\
				ft_str_iter.c		\
				ft_str_read.c		\
				ft_str_read2.c		\
				ft_str_write.c		\
				ft_print_nbr_base.c	\
                ft_printf.c			\
			)
OBJ		=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)



# ---------------------------------- TARGETS -----------------------------------

all: $(NAME)

$(NAME): $(OBJ)
	ar -rc $@ $^

# This rule only generates one file, which allows to not relink (meaning it will
# not recompile every sources when a source changes).
# Can be called with `make obj/ft_strlen.o`
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

re: fclean all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

print:
	@echo "\n-------------------- FILES --------------------\n"
	@echo "NAME		$(NAME:%=\n%)\n"
	@echo "INC		$(INC:%=\n%)\n"
	@echo "SRC		$(SRC:%=\n%)\n"
	@echo "OBJ		$(OBJ:%=\n%)\n"
	@echo "\n-------------------- FLAGS --------------------\n"
	@echo "CFLAGS	$(CFLAGS:%=\n%)\n"
