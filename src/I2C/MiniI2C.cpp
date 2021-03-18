
#include "MiniI2C.h"

void MiniI2C::begin(uint8_t ver, uint8_t ch){
    HTcolor._ver = ver;
    HTcolor._ch = ch;
    HTcompass._ver = ver;
    HTcompass._ch = ch;
    PIXYcam._ver = ver;
    PIXYcam._ch = ch;

    MXctrl._ver = ver;
    MXctrl._ch = ch;
    MXctrl.begin();
}