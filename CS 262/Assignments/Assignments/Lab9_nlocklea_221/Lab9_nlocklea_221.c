/* Nicholas Locklear
 * G01090642
 * CS 211
 * Lab 9
 * For some reason the "putting back together" of the bits doesnt work properly. Oops
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0)
#define PRINTBIN(x) printf(BYTETOBINARYPATTERN, BYTETOBINARY(x));
#if CHAR_BIT!=8 
#error Unsupported byte size (CHAR_BIT!=8) 
#endif

/* Check Ex: 6 */
int isNumber(char number[]){
	int i = 0;
	if (number[0] == '-'){
		i = 1;
	}
	for(i=i; i < strlen(number); i++){
        	if(!isdigit(number[i])){
			return 0;
		}
    	}
    return 1;
}

void setlsbs(unsigned char *p, unsigned char b0){
	int i;
	int Bit;
	Bit = (b0 & 1);
	printf("Modified Values:\n\n");
	for(i = 7; i >= 0; i--){
		p[i] ^= (-Bit ^ p[i]) & (1UL << i);
		printf("Entry %d is %u : ", (i+1), p[i]);
		PRINTBIN(p[i]);
		printf("\n");

	}
}

unsigned char getlsbs(unsigned char *p){
	unsigned char x = '1';
	int i;
	for(i = 7; i > 0; i--){
		x ^= (-p[i] ^ x) & (1UL << i);

	}
	return x;
}


int main(int argc, char *argv[]){
	int Seed = atoi(argv[1]);
	int i;
	unsigned char p[1024];
	unsigned char byte0;
	srand(Seed);
	byte0 = rand() % 255 + 0;
	printf("Seed: %d\n", Seed);
	if(isNumber(argv[1]) == 0){
		printf("Input [%s] is invalid.\n", argv[1]);
	}

	if (p == NULL){
        	printf("Error allocating memory. Exiting Program.");
        exit(1);
	}
	printf("Byte0 %u is ", byte0);
	PRINTBIN(byte0);
	printf("\n");
	for(i = 0; i < 8; i ++){
		p[i] = rand() % 255 + 0;
		printf("Input %d is %u : ",i +1, p[i]);
		PRINTBIN(p[i]);
		printf("  ");
		p[i] ^= 1UL << 8;
		printf("%u\n", p[i]);
		printf("\n");

	}

	setlsbs(p, byte0);
	printf("Original Bit: %u\n", getlsbs(p));
	
	return 0;
}