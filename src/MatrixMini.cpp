/*!
 * @file MatrixMini.cpp
 *
 * @section author Author
 * Written by
 * @section license License
 * BSD license, all text here must be included in any redistribution.
 *
 */

#include "MatrixMini.h"

/**************************************************************************/
/*!
    @brief  Create the Motor Shield object at an I2C address, default is 0x60
    @param  addr Optional I2C address if you've changed it
*/
/**************************************************************************/
MatrixMini::MatrixMini(uint8_t addr) {
  _addr = addr;
  _pwm = MINI_PWMServoDriver(_addr);
}




/**************************************************************************/
/*!
    @brief  Initialize the I2C hardware and PWM driver, then turn off all pins.
    @param    freq
    The PWM frequency for the driver, used for speed control and microstepping.
    By default we use 1600 Hz which is a little audible but efficient.
    @param    theWire
    A pointer to an optional I2C interface. If not provided, we use Wire or Wire1
    (on Due)
*/
/**************************************************************************/
void MatrixMini::begin(uint16_t freq) {

  _i2c = &Wire;
  // init PWM w/_freq
  _i2c->begin();
  _pwm.begin();
  _freq = freq;
  _pwm.setPWMFreq(_freq);  // This is the maximum PWM frequency
  for (uint8_t i=0; i<16; i++)
    _pwm.setPWM(i, 0, 0);


	// Init Modules:
	M1.begin(&_pwm, 0, 1, 2);
	M2.begin(&_pwm, 5, 4, 3);

	RC1.begin(&_pwm, 6);
	RC2.begin(&_pwm, 7);
	RC3.begin(&_pwm, 8);
	RC4.begin(&_pwm, 9);

	LED1.begin(&_pwm, 14, 13, 15);
	LED2.begin(&_pwm, 11, 10, 12);

	BTN1.begin(8);
	BTN2.begin(7);

	D1.begin(2);
	D2.begin(3);
	D3.begin(4);
	D4.begin(5);

	ANG1.begin(A0); //first pin of Mini's A1 Port
	ANG2.begin(A1); //first pin of Mini's A2 Port
	ANG3.begin(A2); //first pin of Mini's A3 Port

	US1.begin(3,2);
	US2.begin(4,3);
	US3.begin(5,4);
	US4.begin(6,5);
}
