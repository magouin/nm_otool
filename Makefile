SRC_NAME =	ft_nm.c \
			fat_bin.c \
			macho_32.c \
			macho_64.c \
			get_index_32.c \
			get_index_64.c \
			print_32.c \
			print_64.c

INC_PATH = ./includes
OBJ_PATH = ./obj/

LIB_NAME = libft.a

NAME = ft_nm

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

SRC_PATH = ./srcs/

OBJ_PATH = ./obj/

LIB_PATH = ./libft/

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = $(addprefix $(LIB_PATH), $(LIB_NAME))

all : $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME) : $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(INC) $^ -o $@ $(LIB)

clean:
	make clean -C libft
	/bin/rm -f $(OBJ)
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
