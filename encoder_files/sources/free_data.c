#include "encoder.h"

void	free_list(t_list *leafs) {

	node *aux = leafs->start;
	node *aux2;;
	
	while (aux->next != NULL){
		aux2 = aux;
		aux = aux->next;
		free(aux2);
	}
	free(aux);
}

void	delete_tree(node* node)
{
	if (node == NULL)
		return;
	delete_tree(node->left);
	delete_tree(node->right);
	free(node);
}

void	delete_dictionary(char **dictionary)
{
	for (int i = 0; i < EXTEND_ASCII_SIZE; i++)
		free(dictionary[i]);
	free(dictionary);
}

void	free_data(t_data *data, t_return *data_info)
{
	
	if (data->tree != NULL)
		delete_tree(data->tree);
	if (data->dictionary != NULL)
		delete_dictionary(data->dictionary);
	if (data->code != NULL)
		free(data->code);
	if (data_info != NULL)
		free(data_info->decode_data);
}