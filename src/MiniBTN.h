#ifndef _MINIBTN_H_
#define _MINIBTN_H_

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
