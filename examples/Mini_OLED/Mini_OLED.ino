#include <MatrixMini.h>

int precent;

void setup() {
    Mini.begin(LI_2);
    Mini.D4.Serial.begin(115200); // set up Serial library at 115200 bps

    Mini.D4.Serial.println("MATRIX+RST"); // Set module in Active mode 
    delay(1000);

    Mini.D4.Serial.println("MATRIX+SLEEP=0"); // Set module in Active mode 
    delay(10);
    Mini.D4.Serial.println("MATRIX+DISPLAY=1"); // Set display in reverse mode
    delay(10);
    Mini.D4.Serial.println("MATRIX+LINE=1"); // Set display line at 1
    delay(10);
}

void loop() {
    precent = map(Mini.A1.getANG(), 0, 1023, 0, 100);
    Mini.D4.Serial.println(String(precent)+"%");
    delay(100);
}