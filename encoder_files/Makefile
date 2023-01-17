NAME			=	encoder

PATH_LIBFT		=	./libft
LIBFT			=	$(PATH_LIBFT)/libft.a
PATH_ENCODER	= 	

I_LIBFT			=	-I ./libft
I_INCLUDE		=	-I ./include

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra -g

SRC_DIR			=	sources

SRC_FILES		=	main.c\
					fill_and_sort_ascii.c\
					create_list.c\
					create_huffman_tree.c\
					make_dictionary.c\
					encoder.c\
					compact_data.c\
					share_memory.c\
					decoder.c\
					print_data_struct.c\
					free_data.c\

SRC				=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR			=	objects
OBJ				=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADER			=	./encoder/encoder.h\


all:	$(NAME)

$(NAME):	$(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(I_INCLUDE) $(I_LIBFT)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(I_INCLUDE) $(I_LIBFT)

$(LIBFT):
	make -C $(PATH_LIBFT)

$(OBJ_DIR):
	mkdir objects

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
	make -C $(PATH_LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(PATH_LIBFT) fclean

re: fclean all

valgrind: re
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) file1 file2