#include "encoder.h"


void	compact_data(char *encode, char c_data[], int n_char)
{
	int	z;

	ft_bzero(c_data, n_char);

	z = 0;
	for (int i = 0; i < n_char; i++)
	{
		for (int j = 0; j < BYTE_SIZE ; j++)
		{
			if (encode[z] == '\0')
				break;
			if (encode[z] == '1'){
				c_data[i] |= c_data[i] | 1 << j;
			}
			else
				if (c_data[i] << j == 1)
					c_data[i] ^= 1 << j;
			z++;
		}
	}
}