#include "util.h"

void swap(byte * p1, byte * p2) {
    byte tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}
