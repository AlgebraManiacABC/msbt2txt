#include "print_wide.h"

void print_wide(int hex)
{
	fprint_wide(stdout,hex);
}

void fprint_wide(FILE *out, int hex)
{
	int bytes = 0;
	byte wide[7]={0};
	if(hex > 0xffff)
	{
		//	From UTF 32
		//	11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		//	Max 4-byte char: 0x001fffff
		//	111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		//	Max 5-byte char: 0x03ffffff
		//	1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		//	Max 6-byte char: 0x7fffffff
		//	11111110 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		//	Max 7-byte char (with 32 bits) = 0xffffffff
		if(hex > 0x7fffffff)
		{
			bytes = 7;
			wide[0]=0b11111110;
		}
		if(hex > 0x03ffffff)
		{
			bytes = 6;
			wide[0]=0b11111100;
		}
		if(hex > 0x001fffff)
		{
			bytes = 5;
			wide[0]=0b11111000;
		}
		else
		{
			bytes = 4;
			wide[0]=0b11110000;
		}
	}
	else if(hex > 0x7f)
	{
		//	From UTF 16
		//	110xxxxx 10xxxxxx
		//	Max 2-byte char: 0x07ff
		//	1110xxxx 10xxxxxx 10xxxxxx
		//	Max 3-byte char: 0xffff
		if(hex > 0x07ff)
		{
			bytes = 3;
			wide[0]=0b11100000;
		}
		else
		{
			bytes = 2;
			wide[0]=0b11000000;
		}
	}
	else
	{
		//	ASCII: 7 bits
		//	01111111
		//	Max 1-byte char: 0x7f
		fprintf(out,"%lc",hex);
		return;
	}
	int c = bytes-1;
	for(int i=1; i<=c; i++)
	{
		wide[i]=0b10000000;
	}
	wide[0] |= hex >> (6*c);
	for(int i=1; i<=c; i++)
	{
		wide[i] |= (hex >> (6 * (c-i))) & 0b111111;
	}
	fwrite(wide,sizeof(byte),bytes,out);
	return;
}