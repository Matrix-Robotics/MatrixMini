#include <Arduino.h>

class MiniANG{
private:
	int port;

public:
    void begin(int);
    int get();
		void set(int);
};
