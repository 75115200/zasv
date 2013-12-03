/*************************************************************************
    > File Name:     hexDump.c
    > Author:        Landerl Young
    > Mail:          LanderlYoung@gmail.com 
    > Created Time:  2013/6/23 18:15:02
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void hexDump(/*unsigned*/ char str[], int off, int len) {
#define HEX_LINE_LEN 16
	int index = 0, i;
	char buf[HEX_LINE_LEN + 2] = {0};
	char charPrintableFilter(char c) {
		unsigned cc = (unsigned char)c;
		return (cc > 126 && cc < 128) || cc < 32 ? '.' : c;
	}

	if(off == 0)
		printf("           0  1  2  3  4  5  6  7  8   9  A  B  C  D  E  F\n"
				"-------------------------------------------------------------------------------\n");
	while(len - index >= HEX_LINE_LEN) {
		printf("%08X: ", off);
		for(i = 0; i <= HEX_LINE_LEN; i++) {
			printf("%02X ",(unsigned char)str[index]);
			buf[i] = charPrintableFilter(str[index++]);
			if(i == HEX_LINE_LEN / 2 - 1 )
				putchar(' '), buf[++i] = ' ';
			off++;
		}
		printf(" |%s|\n", buf);
	}
	if(len - index > 0) {
		printf("%08X: ", off);
		for(i = 0; i <= HEX_LINE_LEN; i++) {
			if(index < len) {
				printf("%02X ",(unsigned char)str[index]);
				buf[i] = charPrintableFilter(str[index++]);
			} else {
				buf[i] = ' ';
				printf("   ");
			}
			if(i == HEX_LINE_LEN /2 - 1 )
				putchar(' '), buf[++i] = ' ';
			off++;
		}
		printf(" |%s|\n", buf);
	}
#undef HEX_LINE_LEN
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		fprintf(stderr, "hexdump [file]\n");
		exit(1);
	} else {
		FILE *f = fopen(argv[1], "rb");
		char buf[1024];
		size_t size;
		size_t total = 0;
		if(f == NULL) {
			fprintf(stderr, "Open file %s failed.", argv[1]);
			exit(1);
		}
		while((size = fread(buf, sizeof(char), 1024, f)) > 0) {
			hexDump(buf, total, size);
			total += size;
		}
		fclose(f);
	}
	return 0;
}
