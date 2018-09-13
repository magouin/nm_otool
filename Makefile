SRC_NAME =	ft_nm.c \
			fat_bin.c \
			macho_32.c \
			macho_64.c \
			get_index_32.c \
			get_index_64.c \
			print_32.c \
			print_64.c \
			dup.c \
			print.c

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

O_SRC_NAME =	ft_otool.c \
				dup.c \
				otool_32.c \
				otool_64.c \
				fat_bin_o.c \
				print.c

O_INC_PATH = ./includes
O_OBJ_PATH = ./obj/

O_LIB_NAME = libft.a

O_NAME = ft_otool

O_CC = gcc

O_CFLAGS = -Wall -Werror -Wextra -g

O_SRC_PATH = ./srcs/

O_OBJ_PATH = ./obj/

O_LIB_PATH = ./libft/

O_OBJ_NAME = $(O_SRC_NAME:.c=.o)

O_SRC = $(addprefix $(O_SRC_PATH),$(O_SRC_NAME))
O_OBJ = $(addprefix $(O_OBJ_PATH),$(O_OBJ_NAME))
O_INC = $(addprefix -I,$(O_INC_PATH))
O_LIB = $(addprefix $(O_LIB_PATH), $(O_LIB_NAME))

all : $(NAME) $(O_NAME)

$(OBJ_PATH)%.o: $(O_SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(O_OBJ_PATH)%.o: $(O_SRC_PATH)%.c
	@mkdir $(O_OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(O_CC) $(O_CFLAGS) $(O_INC) -o $@ -c $<

$(NAME) : $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(INC) $^ -o $@ $(LIB)

$(O_NAME) : $(O_OBJ)
	$(O_CC) $(O_CFLAGS) $(O_INC) $^ -o $@ $(O_LIB)

clean:
	make clean -C libft
	/bin/rm -f $(OBJ)
	/bin/rm -rf $(OBJ_PATH)
	/bin/rm -f $(O_OBJ)
	/bin/rm -rf $(O_OBJ_PATH)


fclean: clean
	make fclean -C libft
	rm -f $(NAME)
	rm -f $(O_NAME)

re: fclean all

.PHONY : all clean fclean re
