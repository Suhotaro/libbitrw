#include <stdio.h>

#include "../src/bitrw.h"

int main()
{	
	int ret = 0;
	int num = 1;
	
	ret = bitrw_init("write.txt");
	if (ret == 0)
	{
		printf("ERROR: open file\n");
		return 0;
	}

	int val = bitrw_read();
	while(val != -1)
	{
		if (num == 8)
		{
			printf("%d\n", val);
			num = 0;
		}
		else
			printf("%d", val);

		val = bitrw_read();	
		num++;
	}
	
	bitrw_deinit();
	
	return 0;
}
