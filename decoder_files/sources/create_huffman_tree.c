#include "decoder.h"

static node	*remove_initial_node(t_list *leafs)
{
	node	*aux = NULL;

	if (leafs->start != NULL) {
		aux = leafs->start;
		leafs->start = aux->next;
		aux->next = NULL;
		leafs->size--;
	}
	return (aux);
}

static void	insert_new_to_list(t_list *leafs, node *new) {

	node	*aux;

	if (leafs->start == NULL) {
		leafs->start = new;
	}
	else if (new->frequency < leafs->start->frequency) {
		new->next = leafs->start;
		leafs->start = new;
	}
	else {
		aux = leafs->start;
		while (aux->next != NULL && aux->next->frequency <= new->frequency)
			aux = aux->next;
		new->next = aux->next;
		aux->next = new;
	}
	leafs->size++;
}

node	*create_huffman_tree(t_list *leafs)
{
	node	*first;
	node	*second;
	node	*new;

	while (leafs->size > 1)
	{
		first = remove_initial_node(leafs);
		second = remove_initial_node(leafs);
		new = malloc(sizeof(node));
		if (new == NULL) {
			printf("malloc Error!!!!");
			break;
		}
		else {
			new->character = '-';
			new->frequency = first->frequency + second->frequency;
			new->left = first;
			new->right = second;
			new->next = NULL;
			insert_new_to_list(leafs, new);
		}
	}
	return (leafs->start);
}
