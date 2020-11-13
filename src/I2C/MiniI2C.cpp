
#include "MiniI2C.h"

void MiniI2C::begin(int ver, byte ch){
    HTC._ch = ch;
    HTC._ver = ver;
}
    