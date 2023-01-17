#ifndef ENCODER_H
#define ENCODER_H

#include "libft.h"
#include <stdio.h>
#include <string.h>
/*OPEN FUNCTION*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*MALLOC FUNCTION*/
#include <stdlib.h>
/*READ FUNCTION*/
#include <unistd.h>
/*SHARE MEMORY FUNCTIONS*/
#include <sys/ipc.h>
#include<sys/shm.h>

/*SHARE MEMORY REFERENCE FOR FTOK FUNCTION*/
#define FILENAME			"../shmfile.c"


#define BYTE_SIZE			8
#define EXTEND_ASCII_SIZE	256


typedef struct s_node {

	unsigned char	character;
	int				frequency;
	struct s_node*	next;
	struct s_node*	right;
	struct s_node*	left;
	struct s_node*	p;
}node;

typedef struct s_list{
	node*	start;
	int		size;
}t_list;

typedef struct s_return {
	char	*decode_data;
	int		decode_bits_size;
	int		compress_bits_size;

}t_return;

typedef struct s_data {
	unsigned char	ascii_char[EXTEND_ASCII_SIZE];
	int				ascii_frequency[EXTEND_ASCII_SIZE];
	int				unsorted_frequency[EXTEND_ASCII_SIZE];
	t_list			leafs;
	node			*tree;
	char			**dictionary;
	char			*code;
	int				n_bits_compressed;
	clock_t			start;
	clock_t			end;
	double			run_time;
}t_data;

void	fill_and_sort_ascii(int argc, char *argv[], t_data *data);

void	create_list(t_data *data);

node	*create_huffman_tree(t_list *leafs);

char	**make_dictionary(node *tree);

int		encoder(t_data *data, int argc, char *argv[]);

void	decoder(char *encode, node *root);

void	compact_data(char *encode, char c_data[], int n_char);

char	*share_memory(char *c_data, int data_size, 
						t_return *data_info, t_data *data);

void	open_file(int *fd, char *filename);

void	free_list(t_list *leafs);

void	delete_tree(node* node);

void	delete_dictionary(char **dictionary);

void	free_data(t_data *data, t_return *data_info);

void	print_struct_data(t_data *data, char *c_data, int data_size);

#endif