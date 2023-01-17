#ifndef ENCODER_H
#define ENCODER_H

#include "libft.h"
#include <stdio.h>
#include <string.h>
//open function
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//malloc
#include <stdlib.h>
//read function
#include <unistd.h>
//share memory
#include <sys/ipc.h>
#include<sys/shm.h>
//calculate the decoder running time
#include <time.h>

//share memory file reference
#define FILENAME 			"../shmfile.c"

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

typedef struct s_compress {
	char	*data;
	int		n_bits;
	int		n_bytes;
}t_compress;

typedef struct s_unziped {
	char	*bits_data;
	int		n_bits;
	int		n_bytes;
	char	*decode_data;
	int		decode_size;
	int		decode_bits_size;
}t_unziped;

typedef struct s_data {
	unsigned char	ascii_char[256];
	int				ascii_frequency[256];
	t_list			leafs;
	node			*tree;
	char			**dictionary;
	clock_t			start;
	clock_t			end;
	double			run_time;
}t_data;

void	fill_and_sort_ascii(t_data *data);

void	create_list(t_data *data);

node	*create_huffman_tree(t_list *leafs);

char	**make_dictionary(node *tree);

int		encoder(char **dictionary, char *argv[], char **encode);

void	decoder(node *root, t_unziped *u_data);

void	decompress_data(t_compress *c_data, t_unziped *u_data);

void	read_share_memory(t_compress *c_data, t_data *data);

void	write_share_memory(t_data *data, t_unziped *u_data, t_compress *c_data);

void	open_file(int *fd, char *filename);

void	free_list(t_list *leafs);

void	free_data(t_data *data, char *c_data, char *cdata_bits, char *decode);

void	print_data_struct(t_data *data);

#endif