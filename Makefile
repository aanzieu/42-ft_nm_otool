# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/06 11:15:53 by aanzieu           #+#    #+#              #
#    Updated: 2019/03/03 14:52:58 by aanzieu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm

MAKE = make
MAKE_FLAGS = --no-print-directory


LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
#endif

INCLUDE = -I include/ -I libft

CC = gcc -g
CC_FLAGS = -Wall -Werror -Wextra

RM = rm -f
RF = rm -rf

###########################
##--- LIST of Sources ---##
###########################
SRC_DIR = src

SRC =	$(SRC_DIR)/ft_nm/main.c \
		\
		$(SRC_DIR)/ft_nm/handles/nm.c \
		$(SRC_DIR)/ft_nm/handles/handle_32.c \
		$(SRC_DIR)/ft_nm/handles/typechar_32.c \
		$(SRC_DIR)/ft_nm/handles/printsym_32.c \
		$(SRC_DIR)/ft_nm/handles/loadcmd_32.c \
		\
		$(SRC_DIR)/ft_nm/handles/handle_64.c \
		$(SRC_DIR)/ft_nm/handles/typechar_64.c \
		$(SRC_DIR)/ft_nm/handles/listsort_64.c \
		$(SRC_DIR)/ft_nm/handles/listsort_32.c \
		$(SRC_DIR)/ft_nm/handles/printsym_64.c \
		$(SRC_DIR)/ft_nm/handles/loadcmd_64.c \
		\
		$(SRC_DIR)/utils/print.c \
		$(SRC_DIR)/utils/swap_magic.c \
		$(SRC_DIR)/utils/get_arch_type.c \
		$(SRC_DIR)/utils/swap_bits.c \
		$(SRC_DIR)/utils/checkoff.c \
		$(SRC_DIR)/utils/lstsort.c \
		$(SRC_DIR)/utils/utils_open.c \
		$(SRC_DIR)/utils/utils_print.c \

###########################################
##--- Use Patsubst to find .o from .c ---##
###########################################

OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
.SILENT:

###############################
##--- Compilation Running ---##
###############################

all: $(NAME)

$(NAME): $(OBJ)
	printf '\033[K\033[32m[✔] %s\n\033[0m' "--Compiling Sources--------"
	@$(MAKE) $(MAKE_FLAGS) -C $(LIBFT_DIR)
	if [ ! -d bin ]; then mkdir -p bin; fi
	$(CC) $(CC_FLAGS) -o bin/$(NAME) $(OBJ) $(LIBFT)
	printf '\033[1;7m'
	printf '\033[33m[✔] %s\n\033[0m' "--DONE--------"

###################################################
##--- Create repertories for objects .c to .c ---##
###################################################

obj/%.o: src/%.c
	if [ ! -d obj ]; then mkdir -p obj; fi
	if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CC_FLAGS) -c $(INCLUDE) $< -o $@
	printf '\033[K\033[0m[✔] %s\n\033[0m\033[1A' "$<"

##############################
##--- Clean only objects .o ##
##############################

clean:
	printf '\033[1;7m'
	printf '\033[31m[✔] %s\n\033[0m' "--Cleaning Library--------"
	@$(MAKE) $(MAKE_FLAGS) fclean -C $(LIBFT_DIR)
	printf '\033[1;7m'
	printf '\033[31m[✔] %s\n\033[0m' "--Cleaning Output Files--------"
	@$(RM) $(OBJ)

###################################################
##--- Clean ALl                                  ##
###################################################

fclean: clean
	printf '\033[1;7m'
	printf '\033[31m[✔] %s\n\033[0m' "--Cleaning Executable and All Object--------"
	@$(RM) $(NAME)
	@$(RF) obj bin

re: fclean all

.PHONY: all clean fclean re