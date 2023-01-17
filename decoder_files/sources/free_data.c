#include "decoder.h"

static void	delete_tree(node* node)
{
	if (node == NULL)
		return;
	delete_tree(node->left);
	delete_tree(node->right);
	free(node);
}


static void	delete_dictionary(char **dictionary) {

	for (int i = 0; i < 256; i++)
		free(dictionary[i]);
	free(dictionary);
}

void	free_data(t_data *data, char *c_data, char *cdata_bits, char *decode)
{
	delete_tree(data->tree);
	delete_dictionary(data->dictionary);
	free(cdata_bits);
	free(c_data);
	free(decode);
}