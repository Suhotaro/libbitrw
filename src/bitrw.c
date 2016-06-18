#include <stdio.h>
#include <stdlib.h>

/* TODO: make it cross-patform */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "bitrw.h" 

bitrw_data_ptr bitrw = NULL;

int
bitrw_init(const char *file_name)
{
	int fd;
	
	if (file_name == NULL)
	{
		printf("ERROR: file is NULL\n");
		return 0;
	}
	
	fd = open(file_name, O_RDWR | O_CREAT);
	if (fd < 0)
	{
		printf("ERROR: open file %s\n", file_name);
		return 0;
	}
	
	bitrw = malloc(sizeof(bitrw_data));
	if (bitrw == NULL)
	{
		printf("ERROR: alloc\n");
		return 0;
	}
	
	bitrw->fd = fd;
	bitrw->curr_pos = 0;
	bitrw->data = 0x00;
	bitrw->first_write = 1;
	bitrw->first_read = 1;
	
	return 1;
}

void
bitrw_deinit(void)
{	
	if (bitrw)
	{
		if (bitrw->fd > 0)
			close(bitrw->fd);
		free(bitrw);
	}
}

int
bitrw_read(void)
{
    int val = 0;
	
	/* if (bitrw->curr_pos < 0 || bitrw->first_read == 1) */
	if (bitrw->curr_pos == 8 || bitrw->first_read == 1)	
	{
		val = read(bitrw->fd, &bitrw->data, 1);
		if (val == 0)
			return -1;
	
		/* bitrw->curr_pos = 7; */
		bitrw->curr_pos = 0;
	}
   
	val = !!(bitrw->data & (1 << bitrw->curr_pos));
	/* bitrw->curr_pos -= 1; */
	bitrw->curr_pos += 1;

	/* TODO: put it in "if statment" based on gcc "fast if" feture */
	bitrw->first_read = 0;
		
	return val;
}

void 
bitrw_write(int val, int flush)
{
	if (val < 0 || val > 1)
	{
		printf("ERROR: val is not valid, 1 or 0 should be used\n");
		return;
	}	

	/* TODO: support little-indian*/
	bitrw->data |= (val << bitrw->curr_pos);
	bitrw->curr_pos += 1;

	if (flush == 1 ||
	   (bitrw->curr_pos == 8 &&
	    bitrw->first_write == 0))
	{
		/* TODO: proccess last byte correctly */
		write(bitrw->fd, &bitrw->data, 1);
		bitrw->curr_pos = 0;
		bitrw->data = 0x00;
	}
	
	/* TODO: put it in "if statment" based on gcc "fast if" feture */
	bitrw->first_write = 0;
}

void bitrw_flush()
{
	write(bitrw->fd, &bitrw->data, 1);
	bitrw->curr_pos = 0;
	bitrw->data = 0x00;
}