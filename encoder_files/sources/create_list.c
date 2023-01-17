#include "encoder.h"

static void	init_list(t_list *leafs)
{
	leafs->start = NULL;
	leafs->size = 0;
}

static void	push_back(t_list *leafs, node *new)
{
	node	*aux;

	if (leafs->start == NULL) {
		leafs->start = new;
	}
	else {
		aux = leafs->start;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
	leafs->size++;
}

static void	fill_list(t_data *data)
{
	int i;
	node	*new = NULL;

	i = 0;
	while (data->ascii_frequency[i] == 0)
		i++;
	while (i < EXTEND_ASCII_SIZE)
	{
		new = malloc(sizeof(node));
		if (new == NULL) {
			printf("malloc Error!!!!");
			if (&(data->leafs) != NULL)
			free_list(&(data->leafs));
			exit(-1);
		}
		else {
			new->character = data->ascii_char[i];
			new->frequency = data->ascii_frequency[i];
			new->left = NULL;
			new->right = NULL;
			new->next = NULL;
			push_back(&data->leafs, new);
		}
		i++;
	}
}

void	create_list(t_data *data) {

	init_list(&(data->leafs));
	fill_list(data);
}