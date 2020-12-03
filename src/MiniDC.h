#include "utility/PCA9685.h"


#define FORWARD 1
#define BACKWARD 0

#define AIN1 2
#define AIN2 1
#define BIN1 3
#define BIN2 4

/** Object that controls and keeps state for a single DC motor */
class MiniDC{
public:
	friend class MatrixMini_;
	void set(int speed);

private:
	int _pin;
	int _speed;
	int _mode;
	int _ver;

	void begin(int ver, int pin);
	
	void setMode_PCA9685();
};