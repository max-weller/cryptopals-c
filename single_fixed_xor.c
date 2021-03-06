#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "convlib.c"
#include "fdist_helper.c"




int main(int argc, char** argv) {
	unsigned char key = 0, crack = 0, outstyle = STRING;
	float maxfdev = 0.0f;
	size_t dlen = 0; unsigned char* data;
	unsigned char probdist[256];
	int opt;
	while ((opt = getopt(argc, argv, "ck:d:Hp:P:")) != -1) {
		switch (opt) {
		case 'c':
			crack = 1;
			break;
		case 'P':
			maxfdev = strtof(optarg, NULL);
			break;
		case 'p':
			if (strlen(optarg) != 256*2) {
				fprintf(stderr, "frequency distribution string must be 256 hex bytes\n"); exit(1);
			}
			hex2bin(optarg, probdist, 256);
			break;
		case 'k':
			key = (unsigned char)strtol(optarg, NULL, 0);
			break;
		case 'd':
			dlen = strlen(optarg)/2;
			data = (unsigned char*) malloc(dlen);
			hex2bin(optarg, data, dlen);
			break;
		case 'H':
			outstyle = HEX;
			break;
		case 'R':
			outstyle = RAW;
			break;
		default: /* '?' */
			fprintf(stderr, "Usage: %s [-k KEY] [-c] [-d HEXDATA]\n",
				argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	if (dlen == 0) { //read binary from stdin
		//HACK maxlen 4096
		printf("reading from stdin ...\n");
		data = (unsigned char*)malloc(4096);
		dlen = read(0, data, 4096);
	}
	if (dlen == 0) {
		printf("have no data!\n");
		return 1;
	}

	unsigned char *dst = (unsigned char*) malloc(dlen);
	if (crack) {
		do {
			fixed_xor(data, dst, key, dlen);
			float fdev = fdist_dev(dst, probdist, dlen);
			if (fdev <= maxfdev) {
				printf("%f\t%d\t", fdev, key);
				printout(outstyle, dst, dlen);
				printf("\n");
			}
			key++;
		} while (key != 0);
	} else {
		fixed_xor(data, dst, key, dlen);
		printout(outstyle, dst, dlen);
	}
}

