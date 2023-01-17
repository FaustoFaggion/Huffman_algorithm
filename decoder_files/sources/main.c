#include "decoder.h"

int main (void) {

	t_data			data;
	t_compress		c_data;
	t_unziped		u_data;

	/*START COUNTING TIME OF DECODING*/
	data.start = clock();

	/*READ MEMORY FROM ENCODER PROCESS*/
	read_share_memory(&c_data, &data);

	/*SORT FREQUENCY OF CHARACTERS SENT BY ENCODER PROCESS*/
	fill_and_sort_ascii(&data);
	
	/*CREATE A SORTED LIST OF CHAR FREQUENCY*/
	create_list(&data);

	/*CREATE A BINARY TREE*/
	data.tree = create_huffman_tree(&data.leafs);
	
	/*MAKE A DICTIONARY O CODE-WORDS BY TRAVESSING THE TREE*/
	data.dictionary = make_dictionary(data.tree);

	/*CREATE A STRING OF CHARACTERS REPRESENTING THE BITS OF THE ARRAY RECEIVED
	BY THE ENCODER PROCESS*/
	decompress_data(&c_data, &u_data);

	/*DECODE THE STRING OF BITS USING THE BINARY TREE*/
	decoder(data.tree, &u_data);

	/*SHARE MEMORY WITH ENCODER PROCESS*/
	write_share_memory(&data, &u_data, &c_data);

	/*FREE MEMORY ALLOCATED ON THE PROCESS*/
	free_data(&data, c_data.data, u_data.bits_data, u_data.decode_data);

	return (0);
}
