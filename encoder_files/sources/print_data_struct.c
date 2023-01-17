#include "encoder.h"

static void	print_ascii_tables(t_data *data)
{
	printf("\n________CHAR FREQUENCY________\n");
	for (int i = 0; i < 256; i++) {
		if (data->ascii_frequency[i] != 0)
			printf("%d - %c: %d\n", i, (char)data->ascii_char[i],
				data->ascii_frequency[i]);
	}
}

static void	print_list(t_list *leafs) {
	
	node *aux = leafs->start;

	printf("\n________LINKED LIST________\n");
	while (aux->next != NULL){
		printf("%c: %d\n", aux->character, aux->frequency);
		aux = aux->next;
	}
	printf("%c: %d \n", aux->character, aux->frequency);
}


static void	print_tree(node *root, int size)
{
	if(root->left == NULL && root->right == NULL)
		printf("leaf: %c higth: %d\n", root->character, size);
	else{
		print_tree(root->left, size + 1);
		print_tree(root->right, size + 1);
	}
}


static void	print_dic(char **dic)
{
	printf("\n________DICTIONARY________\n");
	for (int i = 0; i < 256; i++){
		if (dic[i][0] != '\0')
			printf("%3d: %s\n", i, dic[i]);
	}
}


static void	print_compact_data (char *c_data, int n_char) {
	

	printf("\n________COMPACT DATA________\n\n");

	for (int i = 0; i < n_char; i++) {
		for (int j = 0; j < 8; j++) {
			if (((c_data[i] >> j) & 1) == 1)
				printf("1");
			else
				printf("0");
		}
	}
	printf("\n");
}

void	print_struct_data(t_data *data, char *c_data, int data_size)
{
	print_ascii_tables(data);
	print_list(&(data->leafs));
	printf("\n________HUFFMAN TREE________\n\n");
	print_tree(data->tree, 0);
	print_dic(data->dictionary);
	printf("%s\n", data->code);
	print_compact_data (c_data, data_size);
}