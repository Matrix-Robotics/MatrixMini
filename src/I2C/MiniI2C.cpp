
#include "MiniI2C.h"

// ver is version of MATRIX Mini, range is 1 ~ 3 (integer).
// ch is I2C channel, range is 1 ~ 4 (integer).
void MiniI2C::begin(uint8_t ver, uint8_t ch){
    HTcolor._ver = ver;
    HTcolor._ch = ch;

    HTcompass._ver = ver;
    HTcompass._ch = ch;

    PIXYcam._ver = ver;
    PIXYcam._ch = ch;

    MXcolor._ver = ver;
    MXcolor._ch = ch;
    MXcolor.begin();

    MXmotion._ver = ver;
    MXmotion._ch = ch;
    MXmotion.begin();

    MXlaser._ver = ver;
    MXlaser._ch = ch;
    MXlaser.begin();

    MXmotor._ver = ver;
    MXmotor._ch = ch;
    MXmotor.begin();

    MXservo._ver = ver;
    MXservo._ch = ch;
    MXservo.begin();

    MXctrl._ver = ver;
    MXctrl._ch = ch;
    MXctrl.begin();
}