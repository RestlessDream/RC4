#include "rc4.h"

#include <stdlib.h>
#include "util.h"
#include "stdio.h"

extern const size_t state_size;
int posx = 0;
int posy = 0;
byte state[STATE_SIZE];

/**
 * Initialization and Key-Sheduling Algorithm 
 *
 * A permutration of all 256 possible bytes
 * 
 * @param key - the inital key that will be permutrated
 */
void init(byte * key, size_t key_len) {
    posx = 0;
    posy = 0;

    for (int i = 0; i < state_size; i++) {
        state[i] = (byte)i;
    }

    int j = 0;
    for (int i = 0; i < state_size; i++) {
        j = (j + state[i] + key[i % key_len]) % state_size;
        swap(state + i, state + j);
    }

}

/**
 * Pseudo-random generation algorithm
 *
 * modifies the state and outputs a byte of the key stream
 *
 * @return byte of key stream
 */
byte gen_key() {
    posx = (posx + 1) % state_size;
    posy = (posy + state[posx]) % state_size;

    swap(state + posx, state + posy);

    return state[(state[posx] + state[posy]) % state_size];
}

/**
 * Perform Encryption
 *
 * @param text - plain text, that will be encrypt
 * @param len - length of plain text
 * @param output - result cipher text
 */
void encrypt(byte * text, size_t len, byte * output) {
    for (int i = 0; i < len; i++) {
        output[i] = (byte)(text[i] ^ gen_key());
    }
}

/**
 * Perform Decryption
 *
 * @param text - cipher text, that will be encrypt
 * @param len - length of plain text
 * @param output - result plain text
 */
void decrypt(byte * text, size_t len, byte * output) {
    encrypt(text, len, output);
}
