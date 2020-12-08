#include <Arduino.h>
#include "utility/ADS1015.h"

class MiniANG{
private:
	int pin1;
	int pin2;
	void begin(int, int);

public:
  	int get();
	friend class MatrixMini_;
};
