#include "utility/PCA9685.h"
#include "utility/PCA9633.h"


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
	void set(int);

private:
	int _pin;
    int _ver;
	int _speed;
	int _mode;

	void begin(int, int);
	
	void setMode_PCA9633();
	void setMode_PCA9685();
};