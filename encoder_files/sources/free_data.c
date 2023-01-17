#include "encoder.h"

static void	delete_tree(node* node)
{
	if (node == NULL)
		return;
	delete_tree(node->left);
	delete_tree(node->right);
	free(node);
}

static void	delete_dictionary(char **dictionary)
{
	for (int i = 0; i < EXTEND_ASCII_SIZE; i++)
		free(dictionary[i]);
	free(dictionary);
}

void	free_data(t_data *data, t_return *data_info)
{
	delete_tree(data->tree);
	delete_dictionary(data->dictionary);
	free(data->code);
	free(data_info->decode_data);
}