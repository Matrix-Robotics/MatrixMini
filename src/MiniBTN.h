#include <Arduino.h>

class MiniBTN{
  public:
	int port;
	
    void begin(int);
    bool get();
};