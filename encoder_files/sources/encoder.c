#include "encoder.h"

static int	calc_size_code(char **dictionary, int argc, char *argv[])
{
	int				fd;
	int				size;
	unsigned char	c;

	size = 0;
	for (int i = 1; i < argc; i++){
		open_file(&fd, argv[i]);
		while (read(fd, &c, 1) > 0)
			size = size + ft_strlen(dictionary[(int)c]);
		close(fd);
	}
	return (size + 1);
}

int	encoder(t_data *data, int argc, char *argv[])
{
	int				fd;
	int				size;
	unsigned char	c;
	
	size = calc_size_code(data->dictionary, argc, argv);
	data->code = ft_calloc(size, sizeof(char));
	for (int i = 1; i < argc; i++){
		open_file(&fd, argv[i]);
		while (read(fd, &c, 1) > 0) {
			strcat(data->code, (data->dictionary)[(int)c]);
		}
		close(fd);
	}
	return (size - 1);
}
