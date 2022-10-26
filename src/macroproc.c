#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Macro
{
	char shorthand[31];
	char explanation[201];
} Macro;

void process_macros(FILE *fp_in, FILE *fp_out)
{
	static Macro macros[100] = { 0 };
	int db_makro = 0;

	char line[1001];
	while (fgets(line, 1000, fp_in))
	{
		if (sscanf(line, "#define %s %[^\n]", macros[db_makro].shorthand, macros[db_makro].explanation) == 2)
		{
			db_makro++;
		}
		else
		{
			int sptr = 0;
			while (line[sptr] != '\0')
			{
				bool match = false;

				for (Macro *makro = macros; makro < macros + db_makro; makro++)
				{
					int msptr;
					for (msptr = 0; makro->shorthand[msptr] != '\0' && makro->shorthand[msptr] == line[sptr + msptr]; msptr++)
						;
					if (makro->shorthand[msptr] == '\0' && !isalnum(line[sptr + msptr]))
					{
						for (int rsptr = 0; makro->explanation[rsptr] != '\0' && makro->explanation[rsptr] != '\n'; rsptr++)
							fputc(makro->explanation[rsptr], fp_out);

						sptr += msptr;
						match = true;
						break;
					}
				}

				if (!match)
				{
					fputc(line[sptr++], fp_out);
				}
			}

			fputc('\n', fp_out);
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Usage: macroproc <input.c> <output.c>\n");
		return 1;
	}

	FILE* fp_in = fopen(argv[1], "r");
	if (fp_in == NULL)
	{
		perror("Couldn't open the input file");
		return 1;
	}
	
	FILE* fp_out = fopen(argv[2], "w");
	if (fp_out == NULL)
	{
		perror("Couldn't open the output file");
		return 1;
	}
	
	process_macros(fp_in, fp_out);
	
	fclose(fp_in);
	fclose(fp_out);

	return 0;
}
