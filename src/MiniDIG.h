#include <Arduino.h>

class MiniDIG{
private:
	int port;
	int mode;
	
	void updateMode(int);
	
public:
    void begin(int);
    bool get();
	void set(byte);
};