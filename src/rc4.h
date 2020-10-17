/*
 * RC4 Algorithm realization
 *
 * Made by Igor Klapatnjuk
 *
 * MIT License
 *
 * Copyright (c) 2020 RestlessDream
 */

#ifndef RC4_
#define RC4_

#include "types.h"

void init(byte * key, size_t key_len);
byte gen_key();
void encrypt(byte * text, size_t len, byte * output);
void decrypt(byte * text, size_t len, byte * output);

#endif
