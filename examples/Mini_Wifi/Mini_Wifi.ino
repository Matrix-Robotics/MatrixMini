#include <MatrixMini.h>

#define SSID "wifi"
#define PASSWORD "12345678"

void setup() {
    Mini.begin();
    Serial.begin(115200);
    Mini.D4.Serial.begin(115200); // set up Serial library at 115200 bps

    sendCommand("AT"); // test command

    sendCommand("AT+CWMODE=1"); // set module in client mode

    wifiConnect(); // connect to local wifi
}

void loop() {
    if(Mini.D4.Serial.available()){
      Serial.write(Mini.D4.Serial.read());
    }
    if(Serial.available()){
        Mini.D4.Serial.write(Serial.read());
    }
}

void wifiConnect(){
    String addr="AT+CWJAP=\"";
    addr+=SSID;
    addr+="\",\"";
    addr+=PASSWORD;
    addr+="\"";
    sendCommand(addr);
}

void sendCommand(String cmd){
    Mini.D4.Serial.print(cmd+"\r\n");
    for (int i=0; i<99; i++){
        if(Mini.D4.Serial.find("OK")){
            Serial.println("OK");
            break;
        }
        else if(i >= 20){
            Serial.print(cmd);
            Serial.println("command fail!");
            break;
        }
        else{
            delay(100);
        }
    }
} 