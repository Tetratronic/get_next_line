#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
	char	*line;

	int fd = open("test.txt", O_RDONLY);
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			printf("%s",line);
			break ;
		}
		printf("%s", line);
		free(line);
	}
}
