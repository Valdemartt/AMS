/*
 * Util.h
 *
 * Created: 20-02-2020 10:43:26
 *  Author: valde
 */ 


#ifndef UTIL_H_
#define UTIL_H_
#define BOOT_START_ADR 
#define PAGESIZE 256
#define TRUE 1
#define FALSE 0
void copy_SRAM_To_Flash();
void copy_Flash_To_SRAM();
typedef volatile unsigned long AddressType;        // Used for passing address to functions
typedef volatile unsigned char __flash* FlashCharPointer; // Used for reading Flash
typedef volatile unsigned int __flash* FlashIntPointer;  // Used for reading Flash


#endif /* UTIL_H_ */