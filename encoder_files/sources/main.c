#include "encoder.h"

static void	init_structs(t_data *data, t_return *data_info)
{
	ft_bzero(data, 1 * sizeof(data));
	ft_bzero(data_info, 1 * sizeof(data_info));
}

void	open_file(int *fd, char *filename)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0){
		perror("");
		exit(2);
	}
}
static void	check_arguments(int argc, char *argv[])
{
	int		fd;
	int		i;
	char	c;
	int		n_char;
	
	if (argc == 1) {
		printf("Wrong number of arguments!!!\n");
		exit(0);
	}
	i = 0;
	n_char = 0;
	for (int j = 1; j < argc; j++){
		open_file(&fd, argv[j]);
		while (read(fd, &c, 1) > 0){
			i++;
			n_char++;
		}
		close(fd);
	}
	if (i == 0){
		printf("Empty files!!\n");
		exit(0);
	}
}

int main (int argc, char *argv[])
{
	t_data		data;
	t_return	data_info;

	check_arguments(argc, argv);

	init_structs(&data, &data_info);
	/*GET FREQUENCY OF CHARACTERS*/
	fill_and_sort_ascii(argc, argv, &data);
	
	/*CREATE A SORTED LIST OF CHAR FREQUENCY*/
	create_list(&data);

	/*CREATE A BINARY TREE*/
	data.tree = create_huffman_tree(&(data.leafs));

	/*MAKE A DICTIONARY O CODE-WORDS BY TRAVESSING THE TREE*/
	data.dictionary = make_dictionary(&data);
	
	/*TRANSLATE THE RECEIVED DATA TRAVESSING THE BINARY TREE TO CREATE A CODE-DATA*/
	data.n_bits_compressed = encoder(&data, argc, argv);

	/*CREATE A STRING THAT CONTAIN ENOUGH BITS TO WRITE THE CODE-STRING INTO THEN*/
	int n_bits = data.n_bits_compressed;
	int data_size = (n_bits % 8 == 0? n_bits / 8 : (n_bits / 8) + 1);
	char	c_data[data_size];

	/*WRITE THE CODED-DATA INTO THE BITS USING BITWISE*/
	compact_data(data.code, c_data, data_size);
	
	/*SHARE MEMORY WITH DECODER PROCESS*/
	data_info.decode_data = share_memory(c_data, data_size, &data_info, &data);

	/*PRINT ON SCREEN DATA RECEIVED FROM DECODER*/
	printf("DADO DESCOMPRIMIDO:\n\n%s\n\n", data_info.decode_data);
	printf("TOTAL DE BITS:	%d\n\n", data_info.decode_bits_size);
	printf("TOTAL BITS COMPRIMIDOS:	%.d\n\n", data_info.compress_bits_size);
	printf("TEMPO OPERAÇÂO DESCOMPRESSÂO:	%.2fms\n\n", data.run_time * 1000);

	/*FREE MEMORY ALLOCATED ON THE PROCESS*/
	free_data(&data, &data_info);

	return (0);
}
