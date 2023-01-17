#include "decoder.h"

static void	sort_frequency(t_data *data)
{
	char	c;
	int		f;
	int		i;

	i = 0;
	while (i < (EXTEND_ASCII_SIZE - 1))
	{
		if (data->ascii_frequency[i] > data->ascii_frequency[i + 1]) {
			f = data->ascii_frequency[i];
			c = data->ascii_char[i];
			data->ascii_frequency[i] = data->ascii_frequency[i + 1];
			data->ascii_char[i] = data->ascii_char[i + 1];
			data->ascii_frequency[i + 1] = f;
			data->ascii_char[i + 1] = c;
			if (i > 0)
				i--;
		}
		else
			i++;
	}
}

static void init_arrays(t_data *data)
{
	for (int i = 0; i < 256; i++) {
		data->ascii_char[i] = (char)i;
	}
}

void	fill_and_sort_ascii(t_data *data)
{
	init_arrays(data);
	sort_frequency(data);
}