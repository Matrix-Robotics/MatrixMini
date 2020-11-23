
#include "MiniI2C.h"

void MiniI2C::begin(int ver, byte ch){
    MC._ch = ch;
    MC._ver = ver;
    MC.init();
}
    