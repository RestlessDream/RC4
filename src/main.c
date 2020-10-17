#include "rc4.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

const size_t BUFFER_SIZE = 64 * 1024;
const size_t block_bsize = 32;
size_t hexs2bin(const char *hex, unsigned char **out);
int hexchr2bin(const char hex, char * out);

int parse_arguments(int argc, char ** argv, FILE ** input, FILE ** output,
        byte * key, size_t * key_len);

int main(int argc, char ** argv) {
    FILE * input;
    FILE * output;
    byte key[32];
    size_t key_len;
    
    if (parse_arguments(argc, argv, &input, &output, key, &key_len) != 0) {
        return 1;
    }

    byte * rbuffer = malloc(BUFFER_SIZE * sizeof(byte));
    byte * wbuffer = malloc(BUFFER_SIZE * sizeof(byte));

    init(key, key_len);
    size_t reads;
    size_t read_blocks;

    while ((reads = fread(rbuffer, sizeof(byte), BUFFER_SIZE, input)) != 0) {
        read_blocks = reads / block_bsize;

        for (size_t i = 0; i < read_blocks; i++) {
            encrypt(rbuffer + block_bsize * i, block_bsize, wbuffer + block_bsize * i);
        }

        if (reads % block_bsize != 0) {
            encrypt(rbuffer + read_blocks * block_bsize, reads % read_blocks,
                            wbuffer + read_blocks * block_bsize);
        }

        if (fwrite(wbuffer, sizeof(byte), reads, output) == 0) {
            fprintf(stderr, "Error occured while writting to the output file.");
            return -1;
        }
    }

    free(rbuffer);
    free(wbuffer);
    fclose(input);
    fclose(output);

    return 0;
}

int parse_arguments(int argc, char ** argv, FILE ** input, FILE ** output,
        byte * key, size_t * key_len) {
    int option;
    int is_all = 0;

    while ((option = getopt(argc, argv, "i:o:k:h")) != -1) {
        switch (option) {
            case 'i':
                *input = fopen(optarg, "r");
                is_all++;
                break;
            case 'o':
                *output = fopen(optarg, "w+");
                is_all++;
                break;
            case 'k':
                *key_len = hexs2bin(optarg, &key);
                is_all++;
                break;
            case '?':
                fprintf(stderr, "%s unsuported flag.", optarg);

                return -2;
            case 'h':
                printf("Usage:  rc4 -i file_path -o file_path -k key [options]\n\n\
RC4 standart decryption\\encyption.\n\
Options:\n\
  -i    Input file path.\n\
  -o    Output file path.\n\
  -k    Given key.\n\
  -h    display this help.\n");

                return 1;
        }
    }

    if (is_all < 3) {
        fprintf(stderr, "Needs to satisfy all parameters, use -h for help.\n");

        return -3;
    }

    return 0;
}

size_t hexs2bin(const char *hex, unsigned char **out) {
	size_t len;
	char   b1;
	char   b2;
	size_t i;

	if (hex == NULL || *hex == '\0' || out == NULL)
		return 0;

	len = strlen(hex);
	if (len % 2 != 0)
		return 0;
	len /= 2;

	memset(*out, 'A', len);
	for (i=0; i<len; i++) {
		if (!hexchr2bin(hex[i*2], &b1) || !hexchr2bin(hex[i*2+1], &b2)) {
			return 0;
		}
		(*out)[i] = (b1 << 4) | b2;
	}
	return len;
}

int hexchr2bin(const char hex, char *out) {
	if (out == NULL)
		return 0;

	if (hex >= '0' && hex <= '9') {
		*out = hex - '0';
	} else if (hex >= 'A' && hex <= 'F') {
		*out = hex - 'A' + 10;
	} else if (hex >= 'a' && hex <= 'f') {
		*out = hex - 'a' + 10;
	} else {
		return 0;
	}

	return 1;
}
