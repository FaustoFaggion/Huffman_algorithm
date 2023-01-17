#include "encoder.h"

void	decoder(char *encode, node *root)
{
	int		i;
	int		j;
	node	*aux = root;
	char	*compress_data = ft_calloc(ft_strlen(encode) + 1, sizeof(char));

	i = 0;
	j = 0;
	while (encode[i] != '\0') {
		if (encode[i] == '0'){
			if (aux->left != NULL)
				aux = aux->left;
		}else
			aux = aux->right;
		if (aux->left == NULL && aux->right == NULL){
			compress_data[j] = aux->character;
			aux = root;
			j++;
		}
		i++;
	}
}
