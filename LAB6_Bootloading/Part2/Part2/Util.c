/*
 * Util.c
 *
 * Created: 20-02-2020 10:43:07
 *  Author: valde
 */ 
#include "Util.h"

void copy_SRAM_To_Flash()
{
	
}

void copy_Flash_To_SRAM()
{
	
}

void write_flashpage(int flashStartAdr, unsigned char *dataPage)
{
	
}

void write_flashbyte(int flashAdr, unsigned char data)
{
	
}

unsigned char read_flashpage(int flashStartAdr, unsigned char *dataPage)
{
	//Check if address equals start of a page
	if(!(flashStartAdr & (PAGESIZE - 1)))
	{
		for(int i = 0; i < PAGESIZE; ++i)
		{
			dataPage[i] = read_flashbyte(flashStartAdr + i);
		}
		return TRUE;
	}
	return FALSE;
}

unsigned char read_flashbyte(int flashAdr)
{
	return (unsigned char)*((FlashCharPointer)flashAdr);
}


