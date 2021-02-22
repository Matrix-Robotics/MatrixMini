#ifndef _MiniBTN_h_
#define _MiniBTN_h_

#include <Arduino.h>

class MiniBTN {
public:
	friend class MatrixMini_;
	bool get();
private:
	int port;
	void begin(int, int);
};

#endif
