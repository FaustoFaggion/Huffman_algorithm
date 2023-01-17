#include "decoder.h"
#include <stdbool.h>

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

bool	detach_memory_block(char *block, int id)
{
	if (shmdt(block) != -1)
		return (0);
	else { printf("memory id: %d fail to dettach!", id);
		return (1);
	}
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


void	read_share_memory(t_compress *c_data, t_data *data)
{
	char	*block_cdata;
	char	*block_nbytes;
	char	*block_nbits;
	char	*block_f;

	/*GRAB COMPRESSED DATA FROM SHARED MEMORY*/
	block_nbytes = create_memory_block(0, 2);
	memcpy(&(c_data->n_bytes), block_nbytes, 1 * sizeof(int));
	detach_memory_block(block_nbytes, 2);
	destroy_memory_block(FILENAME, 2);

	/*GRAB NUMBER OF BYTES OF COMPRESSED DATA FROM SHARED MEMORY*/
	c_data->data = ft_calloc(c_data->n_bytes + 2, 1 * sizeof(char));
	block_cdata = create_memory_block(0, 1);
	memcpy(c_data->data, block_cdata, (c_data->n_bytes + 2) * sizeof(char));
	detach_memory_block(block_cdata, 1);
	destroy_memory_block(FILENAME, 1);

	/*GRAB THE NUMBER OF BITS OF COMPRESSED DATA FROM SHARED MEMORY*/
	block_nbits = create_memory_block(0, 3);
	memcpy(&(c_data->n_bits), block_nbits, 1 * sizeof(int));
	detach_memory_block(block_nbits, 3);
	destroy_memory_block(FILENAME, 3);

	/*GRAB THE FREQUENCY OF CHARACTERS FROM ORIGINAL DATA SHARED MEMORY*/
	block_f = create_memory_block(0, 4);
	memcpy(data->ascii_frequency, block_f, 256 * sizeof(int));
	detach_memory_block(block_f, 4);
	destroy_memory_block(FILENAME, 4);

}

void	write_share_memory(t_data *data, t_unziped *u_data, 
											t_compress *c_data) {
	int		semaphore = 1;

	/*WRITE DECODED TEXT INTO SHARED MEMORY*/
	char	*block_decode = create_memory_block(u_data->decode_size * sizeof(char), 7);
	memcpy(block_decode, u_data->decode_data, u_data->decode_size * sizeof(char));
	detach_memory_block(block_decode, 7);

	/*WRITE DECODED TEXT NUMBER OF BITS INTO SHARED MEMORY*/
	char	*block_decode_size = create_memory_block(1 * sizeof(int), 9);
	memcpy(block_decode_size, &(u_data->decode_bits_size), 1 * sizeof(int));
	detach_memory_block(block_decode_size, 9);

	/*WRITE COMPRESSED TEXT NUMBER OF BITS INTO SARED MEMORY*/
	char	*block_cdata_size = create_memory_block(1 * sizeof(int), 10);
	memcpy(block_cdata_size, &(c_data->n_bits), 1 * sizeof(int));
	detach_memory_block(block_cdata_size, 10);
	
	/*WRITE RUN TIME OF DECODER PROCESS INTO SHARED MEMORY*/
	char	*block_run_time = create_memory_block(1 * sizeof(double), 8);
	data->end = clock();
	data->run_time = (double)(data->end - data->start) / CLOCKS_PER_SEC;
	memcpy(block_run_time, &(data->run_time),  1 * sizeof(double));
	detach_memory_block(block_run_time, 8);

	/*CHANGE THE VALUE OF SEMAPHORE IN THE SHARED MEMORY. ENCODER PROCESS STOP
	LOOP AND START TO READ SHARED MEMORY*/
	char	*block_semaphore = create_memory_block(0, 5);
	memcpy(block_semaphore, &semaphore,  1 * sizeof(int));
	detach_memory_block(block_semaphore, 5);
}
