# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/06 11:15:53 by aanzieu           #+#    #+#              #
#    Updated: 2019/03/18 17:48:26 by aanzieu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_NM = ft_nm
NAME_OTOOL = ft_otool


MAKE = make
MAKE_FLAGS = --no-print-directory

# ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security -g

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
#endif

INCLUDE = -I include/ -I libft

CC = gcc -g
CC_FLAGS = -Wall -Werror -Wextra 
# $(ASAN_FLAGS)

RM = rm -f
RF = rm -rf

###########################
##--- LIST of Sources ---##
###########################
SRC_DIR = src

SRC_PATH_NM = $(SRC_DIR)/ft_nm
SRC_PATH_OTOOL = $(SRC_DIR)/ft_otool
SRC_PATH_MISC = $(SRC_DIR)/utils

SRC_NAME_NM =	$(SRC_PATH_NM)/main.c \
		$(SRC_PATH_NM)/handles/nm.c \
		$(SRC_PATH_NM)/handles/handle_32.c \
		$(SRC_PATH_NM)/handles/handle_64.c \
		$(SRC_PATH_NM)/handles/loadcmd_32.c \
		$(SRC_PATH_NM)/handles/loadcmd_64.c \
		$(SRC_PATH_NM)/handles/typechar_32.c \
		$(SRC_PATH_NM)/handles/typechar_64.c \
		$(SRC_PATH_NM)/handles/handle_fat.c \
		$(SRC_PATH_NM)/handles/handle_static_lyb.c \
		$(SRC_PATH_NM)/handles/listsort_64.c \
		$(SRC_PATH_NM)/handles/listsort_32.c \
		$(SRC_PATH_NM)/handles/printsym_32.c \
		$(SRC_PATH_NM)/handles/printsym_64.c \
		$(SRC_PATH_NM)/handles/print.c \



SRC_NAME_OTOOL =	$(SRC_PATH_OTOOL)/main.c \
		$(SRC_PATH_OTOOL)/handles/ft_otool.c \
		$(SRC_PATH_OTOOL)/handles/handle_32.c \
		$(SRC_PATH_OTOOL)/handles/handle_64.c \
		$(SRC_PATH_OTOOL)/handles/print_path_cpu.c \
		$(SRC_PATH_OTOOL)/handles/handle_static_lyb.c \
		$(SRC_PATH_OTOOL)/handles/parse_arch32.c \
		$(SRC_PATH_OTOOL)/handles/parse_arch64.c \
		$(SRC_PATH_OTOOL)/handles/handle_fat.c \
		$(SRC_PATH_OTOOL)/handles/print_hexdump32.c \
		$(SRC_PATH_OTOOL)/handles/print_hexdump64.c \

		

SRC_NAME_MISC = $(SRC_PATH_MISC)/swap_magic.c \
		$(SRC_PATH_MISC)/swap_magic_fat.c \
		$(SRC_PATH_MISC)/flags_options.c \
		$(SRC_PATH_MISC)/get_arch_type.c \
		$(SRC_PATH_MISC)/swap_bits_uint.c \
		$(SRC_PATH_MISC)/swap_bits_int.c \
		$(SRC_PATH_MISC)/checkoff.c \
		$(SRC_PATH_MISC)/lstsort.c \
		$(SRC_PATH_MISC)/utils_open.c \
		$(SRC_PATH_MISC)/errors.c \
		$(SRC_PATH_MISC)/utils_print.c \
		$(SRC_PATH_MISC)/getoptions.c \
		$(SRC_PATH_MISC)/is_swap.c \

###########################################
##--- Use Patsubst to find .o from .c ---##
###########################################


OBJ_NM = $(patsubst src/%.c, obj/%.o, $(SRC_NAME_NM))
.SILENT:
OBJ_MISC = $(patsubst src/%.c, obj/%.o, $(SRC_NAME_MISC))
.SILENT:
OBJ_OTOOL = $(patsubst src/%.c, obj/%.o, $(SRC_NAME_OTOOL))
.SILENT:

###############################
##--- Compilation Running ---##
###############################

all: $(NAME_NM) $(NAME_OTOOL)

$(NAME_NM): $(OBJ_NM) $(OBJ_MISC)
	printf '\033[K\033[32m[✔] %s\n\033[0m' "--Compiling FT_NM--------"
	@$(MAKE) $(MAKE_FLAGS) -C $(LIBFT_DIR)
	if [ ! -d bin ]; then mkdir -p bin; fi
	$(CC) $(CC_FLAGS) -o bin/$(NAME_NM) $(OBJ_NM) $(OBJ_MISC) $(LIBFT)
	printf '\033[1;7m'
	printf '\033[33m[✔] %s\n\033[0m' "--DONE--------"

$(NAME_OTOOL): $(OBJ_OTOOL) $(OBJ_MISC)
	printf '\033[K\033[32m[✔] %s\n\033[0m' "--Compiling FT_OTOOL--------"
	@$(MAKE) $(MAKE_FLAGS) -C $(LIBFT_DIR)
	if [ ! -d bin ]; then mkdir -p bin; fi
	$(CC) $(CC_FLAGS) -o bin/$(NAME_OTOOL) $(OBJ_OTOOL) $(OBJ_MISC) $(LIBFT)
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
	@$(RM) $(OBJ_NM) $(OBJ_MISC)

###################################################
##--- Clean ALl                                  ##
###################################################

fclean: clean
	printf '\033[1;7m'
	printf '\033[31m[✔] %s\n\033[0m' "--Cleaning Executable and All Object--------"
	@$(RM) $(NAME_NM)
	@$(RF) obj bin

re: fclean all

.PHONY: all clean fclean re