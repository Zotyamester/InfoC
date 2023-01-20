#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 128

char* read_line()
{
	int length = 0;
	char* str = NULL;

	char buf[BUFLEN];
	while (fgets(buf, BUFLEN, stdin))
	{
		char* newline = strchr(buf, '\n');
		int count = (newline != NULL) ? (newline - buf) : (BUFLEN - 1);

		int new_length = length + count;
		char* new_str = (char*)malloc((new_length + 1) * sizeof(char));
		if (new_str == NULL)
		{
			free(str);
			return NULL;
		}

		memcpy(new_str, str, length * sizeof(char));
		memcpy(new_str + length, buf, count * sizeof(char));
		new_str[new_length] = '\0';

		length = new_length;
		str = new_str;

		if (count < BUFLEN - 1)
			break;
	}

	return str;
}

int main(void)
{
	char* line = read_line();
	if (line)
		puts(line);
	free(line);
	return 0;
}
