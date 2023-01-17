#include "decoder.h"

void	decoder(node *root, t_unziped *u_data)
{
	int		i;
	int		j;
	node	*aux = root;
	
	u_data->decode_data = ft_calloc(ft_strlen((u_data->bits_data)) + 1,
															sizeof(char));

	i = 0;
	j = 0;
	u_data->decode_size = 0;
	while ((u_data->bits_data)[i] != '\0') {
		if ((u_data->bits_data)[i] == '0'){
			if (aux->left != NULL)
				aux = aux->left;
		}else
			aux = aux->right;
		if (aux->left == NULL && aux->right == NULL){
			u_data->decode_data[j] = aux->character;
			aux = root;
			j++;
			(u_data->decode_size)++;
		}
		i++;
	}
	u_data->decode_bits_size = u_data->decode_size * 8;
}
