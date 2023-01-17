#include "encoder.h"

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

static int	*char_frequency(int fd, t_data *data, int txt_size)
{
	unsigned char	c;

	while (read(fd, &c, 1) > 0) {
		data->ascii_frequency[(int)c] += 1;
		txt_size++;
	}
	for (int i = 0; i < 256; i++)
		data->unsorted_frequency[i] = data->ascii_frequency[i];


	return (data->ascii_frequency);
}

static void init_arrays(t_data *data)
{
	for (int i = 0; i < EXTEND_ASCII_SIZE; i++) {
		data->ascii_char[i] = (char)i;
		data->ascii_frequency[i] = 0;
		data->unsorted_frequency[i] = 0;
	}
}

void	fill_and_sort_ascii(int argc, char *argv[], t_data *data)
{
	int	fd;
	int	txt_size = 0;

	init_arrays(data);
	for (int i = 1; i < argc; i++){
		open_file(&fd, argv[i]);
		char_frequency(fd, data, txt_size);
		close(fd);
	}
	sort_frequency(data);
}