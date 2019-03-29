#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char file_path[MAX_PATH];
static unsigned char file_buf[32768];

static void replace_ext(const char *s)
{
	ssize_t len, i;

	len = strlen(s);
	if(!len)
		return;

	for(i = len-1; i >= 0; i--)
	{
		if(s[i] == '.')
		{
			memcpy(file_path, s, i);
			memcpy(file_path+i, ".bin", 4);
			return;
		}
	}
}

int main(int argc, char *argv[])
{
	FILE *fin, *fout;
	size_t len, i;

	if(argc != 2)
		return 0;

	/* Open input file */
	fin = fopen(argv[1], "rb");
	if(!fin)
		return 0;

	/* Read 16 RGBA values */
	len = fread(file_buf, 1, 16*4, fin);
	if(len != 16*4)
		return 0;

	/* Replace .pal with .bin */
	replace_ext(argv[1]);

	/* Open output file */
	fout = fopen(file_path, "wb");
	if(!fout)
		return 0;

	for(i = 0; i < 16; i++)
	{
		unsigned char r, g, b;
		unsigned short rgb;

		r = file_buf[i*4+0];
		g = file_buf[i*4+1];
		b = file_buf[i*4+2];

		rgb = 1<<15 | (b/8)<<10 | (g/8)<<5 | (r/8);
		fwrite(&rgb, 2, 1, fout);
	}

	fclose(fin);
	fclose(fout);
}