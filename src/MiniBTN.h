#include <Arduino.h>

class MiniBTN {
public:
	friend class MatrixMini_;
	bool get();
private:
	int port;
	void begin(int, int);
};
