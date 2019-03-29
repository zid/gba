#include <stddef.h>
#include <stdint.h>
#include "gba.h"
#include "data.h"

static void memcpy(void *s1, const void *s2, size_t n)
{
	uint16_t *d;
	const uint16_t *s;

	if(n < 2)
		return;

	if(n&1 == 1)
		while(1);

	d = s1;
	s = s2;

	do
	{
		*d++ = *s++;
	}
	while(n -= 2);
}

void main(void)
{
	DISPCNT = 1<<8;

	BG0CNT = 1<<14 | 31<<8;

	memcpy(PALETTE, bg, bg_size);
	memcpy(VRAM, mess, mess_size);

	int x, y;
	for(y = 0; y < 20; y++)
	{
		for(x = 0; x < 30; x++)
		{
			MAP[y*32+x] = y*30+x;
		}
	}

	while(1)
		;
}