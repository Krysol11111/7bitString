#include <stdio.h>

// bytearray to print, bitsize, how many bits between separators 
void printBinary(char*,int,int);
// bytearray to compress - modifies input!, bitsize
void compressString(char*, int);
// bytearray to decompress, bitsize of input, output buffer
void decompressString(char*, int, char*);


int main( int argc, const char* argv[] )
{
	const int charCount = 8;
	const int bitCount = charCount * 8;
	char origin[charCount];
	strcpy( origin , "kappaaa");
	
	printf("original\n");
	printBinary(origin,bitCount,8);
	
	compressString(origin,bitCount);
	
	printf("compressed\n");
	printBinary(origin,bitCount*7/8,7);
	
	char decompressed[8];
	decompressString(origin,bitCount*7/8,decompressed);
	
	printf("decompressed\n");
	printBinary(decompressed,bitCount,8);

	return 0;
}

void printBinary(char* string, int binaryLength, int betweenBrakes){
	int n;
	for(n = 0; n < binaryLength; n++)
	{
	  unsigned char mask = 1 << (n % 8);
	  if(string[n / 8] & mask)
	  {
	    printf("1");
	  }else{
	  	printf("0");
	  }
	  if (n%betweenBrakes == betweenBrakes-1) printf(" ");
	}
	printf("\n\n");
}

void compressString(char* string, int binaryLength){
	int n;
	int currChar=0;
	int currPos=0;
	for(n = 0; n < binaryLength; n++)
	{
	  if (n%8 == 7) continue;
	  unsigned char mask = 1 << (n % 8);
	  if(string[n / 8] & mask)
	  {
	    string[currChar] |= 1 << (currPos);
	  }else{
	    string[currChar] &= ~(1 << (currPos));
	  }
	  currPos++;
	  if (currPos == 8){
	  	currPos = 0;
	  	currChar++;
	  }
	}
}

void decompressString(char* string, int binaryLength, char* output){
	int n;
	int currChar=0;
	int currPos=0;
	for(n = 0; n < binaryLength; n++)
	{
	  unsigned char mask = 1 << (n % 8);
	  if(string[n / 8] & mask)
	  {
	    output[currChar] |= 1 << (currPos);
	  }else{
	    output[currChar] &= ~(1 << (currPos));
	  }
	  currPos++;
	  if (currPos == 7){
	  	output[currChar] &= ~(1 << (currPos));
	  	currPos = 0;
	  	currChar++;
	  }
	}
}
