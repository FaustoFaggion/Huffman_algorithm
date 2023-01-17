#include "encoder.h"
#include <stdbool.h>

bool	detach_memory_block(char *block, int id)
{
	if (shmdt(block) != -1)
		return (0);
	else { printf("memory id: %d fail to dettach!", id);
		return (1);
	}
}


static int	get_shared_block(char *filename, int size, int id)
{
	key_t	key;
	int		shared_block_id;
	int		fd;

	fd = open(filename, O_CREAT);
	close(fd);
	key = ftok(filename, id);
	if (key == -1){
		printf("Error get KEY shared memory!!\n");
		exit(0);
	}
	if (size == 0)
		shared_block_id =  shmget(key, size, 0);
	else
		shared_block_id =  shmget(key, size, 0644 | IPC_CREAT);
	if (shared_block_id == -1){
		printf("Error get shared memory!!\n");
		exit(0);
	}
	return (shared_block_id);
}

bool	destroy_memory_block(char *filename, int id)
{
	int shared_block_id = get_shared_block(filename, 0, id);

	if (shmctl(shared_block_id, IPC_RMID, NULL) != -1)
		return (0);
	else{
		printf("memory id: %d fail to bedestroyed!", shared_block_id);
		return (1);
	}
	return (0);
}


static char	*create_memory_block(int size, int id)
{
	char	*block;
	int		shared_block_id;

	shared_block_id = get_shared_block(FILENAME, size, id);
	block = shmat(shared_block_id, NULL, 0);
	if (block == NULL) {
		printf("couldn't attach a block of shared memory!!\n");
		exit(0);
	} 
	return (block);
}

char	*share_memory(char *c_data, int data_size, 
					t_return *data_info, t_data *data)
{
	int		semaphore = 0;
	char	*txt;
	int		txt_size = 0;

	/*SHARE MEMORY BLOCK COMPRESSSED DATA*/
	char	*block_cdata = create_memory_block(data_size, 1);
	memcpy(block_cdata, c_data, data_size * sizeof(char));
	detach_memory_block(block_cdata, 1);

	/*SHARE MEMORY BLOCK COMPRESSSED DATA BYTES SIZE*/
	char	*block_datasize = create_memory_block(data_size, 2);
	memcpy(block_datasize, &data_size, 1 * sizeof(int));
	detach_memory_block(block_datasize, 2);

	/*SHARE MEMORY BLOCK COMPRESSSED DATA NUMBER OF BITS*/
	char	*block_nbits = create_memory_block(data->n_bits_compressed, 3);
	memcpy(block_nbits, &(data->n_bits_compressed), 1 * sizeof(int));
	detach_memory_block(block_nbits, 3);

	/*SHARE MEMORY BLOCK FREQUENCY OF CHARACTERS*/
	char	*block_f = create_memory_block(300, 4);
	memcpy(block_f, data->unsorted_frequency, 256 * sizeof(int));
	detach_memory_block(block_f, 4);

	/*SHARE MEMORY BLOCK SEMAPHORE*/
	char	*block_semaphore = create_memory_block(1, 5);
	memcpy(block_semaphore, &semaphore, 1 * sizeof(int));
	
	/*SEMAPHORE WAINTING DECODER PROCESS COMPILE THE INFORMATION AND SEND THE
		DATA BACK. THE VALUE OF BLOCK MEMORY WILL BE CHANGED TO 1 BY DECODER.*/
	write(1, "DATA COMPRESSED\n",16);
	write(1, "Waiting...\n\n", 12);
	while (*block_semaphore == 0)
		sleep(1);

	/*DETACHING AND DESTROYING SEMAPHORE SHARE MEMORY BLOCK*/
	detach_memory_block(block_semaphore, 5);
	destroy_memory_block(FILENAME, 5);
	
	/*SHARE MEMORY BLOCK WITH THE SIZE OF DECODED WRITED BY DECODER PROCESS*/
	char	*block_decode_size = create_memory_block(0, 9);
	memcpy(&(data_info->decode_bits_size), block_decode_size, 1 * sizeof(int));
	detach_memory_block(block_decode_size, 9);
	destroy_memory_block(FILENAME, 9);

	/*SHARE MEMORY BLOCK TO COPY THE TEXT DECODED*/
	char	*block_txt = create_memory_block(0, 7);
	
	/*GET THE NUMBER OF CHARACTERS OF THE TEXT*/
	while (block_txt[txt_size])
	{
		txt_size++;
	}
	txt = ft_calloc(txt_size + 1, sizeof(char));
	memcpy(txt, block_txt, txt_size * sizeof(char));
	detach_memory_block(block_txt, 7);
	destroy_memory_block(FILENAME, 7);

	/*SHARE MEMORY BLOCK TO COPY THE RUN TIME OF DECODER PROCESS*/
	char	*block_run_time = create_memory_block(0, 8);
	memcpy(&(data->run_time), block_run_time, 1 * sizeof(double));
	detach_memory_block(block_run_time, 8);
	destroy_memory_block(FILENAME, 8);

	/*SHARE MEMORY BLOCK TO COPY THE BITS SIZE OF COMPRESS DATA SENT BY ENCODER*/
	char	*block_cdata_size = create_memory_block(0, 10);
	memcpy( &(data_info->compress_bits_size), block_cdata_size, 1 * sizeof(int));
	detach_memory_block(block_cdata_size, 10);
	destroy_memory_block(FILENAME, 10);

	return (txt);
}
