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
	ssize_t len, width, height, x, y, z;

	if(argc != 2)
		return 0;

	fin = fopen(argv[1], "rb");
	if(!fin)
		return 0;

	replace_ext(argv[1]);

	printf("Path: %s\n", file_path);

	fout = fopen(file_path, "wb");
	if(!fout)
		return 0;

	fseek(fin, 0x12, SEEK_SET);
	len = fread(file_buf, 1, 8, fin);
	if(len != 8)
		return 0;

	width  = file_buf[0] | file_buf[1]<<8 | file_buf[2]<<16 | file_buf[3]<<24;
	height = file_buf[4] | file_buf[5]<<8 | file_buf[6]<<16 | file_buf[7]<<24;

	fseek(fin, 0x76, SEEK_SET);
	len = fread(file_buf, 1, 32768, fin);
	fclose(fin);

	for(y = height-1; y >= 7; y -= 8)
	{
		for(x = 0; x < width/2; x += 4)
		{
			for(z = 0; z <= 7; z++)
			{
				unsigned char *p;

				p = &file_buf[(y-z) * width/2 + x];
				p[0] = p[0]>>4 | p[0]<<4;
				p[1] = p[1]>>4 | p[1]<<4;
				p[2] = p[2]>>4 | p[2]<<4;
				p[3] = p[3]>>4 | p[3]<<4;

				fwrite(p, 1, 4, fout);
			}
		}
	}

	fclose(fout);

	return 0;
}