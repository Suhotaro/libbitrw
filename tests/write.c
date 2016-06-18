#include <stdio.h>

#include "../src/bitrw.h"

int main()
{	
	int ret = 0;
	int i = 0;
	/* int arr[16] = {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0}; */
	int arr[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	
	
	ret = bitrw_init("write.txt");
	if (ret == 0)
	{
		printf("ERROR: open file\n");
		return 0;
	}

	for (; i < 16; i++)
		bitrw_write(arr[i], 0);
	
	bitrw_deinit();
	
	return 0;
}