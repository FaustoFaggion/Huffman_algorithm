#include "decoder.h"


void	decompress_data(t_compress *c_data, t_unziped *u_data)
{
	int	z;

	u_data->bits_data = ft_calloc(c_data->n_bits + 1, sizeof(char));
	z = 0;
	for (int i = 0; i < c_data->n_bytes; i++) {
		for (int j = 0; j < BYTE_SIZE; j++) {
			if (((c_data->data[i] >> j) & 1) == 1){
				(u_data->bits_data)[z] = '1';
			}
			else
				(u_data->bits_data)[z] = '0';
			z++;
			if (z == c_data->n_bits)
				break ;
		}
	}
}
