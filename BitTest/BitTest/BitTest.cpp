#include <stdio.h>
#include <stdlib.h>

/*//////STRUCTS//////*/

unsigned char prng(unsigned char x, unsigned char pattern) {
	unsigned char oldbit0 = x & 0x1; /* extract bit 0 */
	unsigned char r = x >> 1;        /* shift right   */
	unsigned char newbit7 = oldbit0 << 7; /* move bit0 to the bit7 pos */
	r = r | newbit7; /* rotate the old value of bit 0 into the bit 7 pos */
	return r^pattern;
}

unsigned char FSR(unsigned char x) {
	unsigned char oldbit0 = x & 0x1; /* extract bit 0 */
	unsigned char r = x >> 1;        /* shift right   */
	unsigned char newbit7 = oldbit0 << 7; /* move bit0 to the bit7 pos */
	r = r | newbit7; /* rotate the old value of bit 0 into the bit 7 pos */
	return r;
}
/*
"data" will be a caller-allocated char array of size "size+1"
(+1 because we need to include an end '\0' char)
"password" will be the starting value for the prng and CAN NOT
be zero.
*/
int crypt(char *data, unsigned int size, unsigned char password) {
	int i = 0;
	unsigned char prngVal = password;
	unsigned char b = 0xb8;
	if (data == NULL) {
		return -1;
	}
	for (i = 0; i < size; i++) {
		prngVal = prng(prngVal, b);
		data[i] = data[i] ^ prngVal;
	}
	return 0;
}

int main(void) {
/*
	unsigned int x = 1;
	x = ~x;
	printf("dec \n%d\n",x);
	printf("hex \n%x\n", x);
	
	while (1) {}

	int i = 0;
	unsigned char x = 0xF;
	unsigned char b = 0xb8;
	for (i = 0; i < 10; i++) {
		x = prng(x, b);
		printf("%x\nw", x);
	}
*/
	unsigned int size = 5;
	unsigned char b = 0xb8;
	char * data = (char *)malloc(sizeof(char)*250);
	scanf("%s", data);
	printf("hello\n");
	printf("%s", data);

	crypt(data, size, b);
	printf("encrypted: %s", data);
	crypt(data, size, b);
	printf("decrypted: %s", data);

	while(1){}
}
