## Get ANG

Get analog data from analog port. <br />
  `A1` means analog port 1. (Options: `A1` / `A2` / `A3`)

```Arduino
uint16_t getANG()
```
<br /><br /><br />
***
<br />

## Get DIG (analog port)

Get digital data from analog port. <br />
  `A1` means analog port 1. (Options: `A1` / `A2` / `A3`)

```Arduino
bool getDIG()
```

### Return

- A **boolean** result of digital data. (`1` / `0`)
<br /><br /><br />
***
<br />

## Get BTN

Get Button is clicked or not. <br />
  `BTN1` means Button 1. (Options: `BTN1` / `BTN2`)

```Arduino
bool get()
```

### Return

- A **boolean** result of BTN is clicked. (`1` / `0`)
<br /><br /><br />
***
<br />

## Get DIG (digital port)

Get digital data from digital port. <br />
  `D1` means digital port 1. (Options: `D1` / `D2` / `D3` / `D4`)

```Arduino
bool get()
```

### Return

- A **boolean** result of digital data. (`1` / `0`)
<br /><br /><br />
***
<br />

## Set DIG

Set digital data to digital port. <br />
  `D1` means digital port 1. (Options: `D1` / `D2` / `D3` / `D4`)

```Arduino
void set(z)
```

### Parameters

- `byte` is a **byte** which you want to set.
<br /><br /><br />
***
<br />

## Get DIG (ultrasonic sensor)

Get digital data from digital port by using ultrasonic sensor. <br />
  `D1` means digital port 1. (Options: `D1` / `D2` / `D3` / `D4`)

```Arduino
float get()
```

### Return

- A **float**  distance of ultrasonic sensor and object.
<br /><br /><br />
***
<br />

## Set Motor

Set DC Motor speed. <br />
  `M1` means Motor port 1. (Options: `M1` / `M2`)

```Arduino
void set(int speed)
```
### Parameters

- `speed` is a **int** of motor speed. (Options: 0~100)
<br /><br /><br />
***
<br />

## Set RC

Set RC Servo angle. <br />
  `RC1` means RC port 1. (Options: `RC1` / `RC2` / `RC3` / `RC4`)

```Arduino
void set(int angle)
```
### Parameters

- `angle` is a **int** of servo angle. (Options: 0~180)
<br /><br /><br />
***
<br />

## Set R

Set LED red color pwm. <br />
  `RGB1` means RGB1 port 1. (Options: `RGB1` / `RGB2`)

```Arduino
void setR(uint8_t PWM)
```
### Parameters

- `PWM` is a **uint8_t** of red color. (Options: 0~255)
<br /><br /><br />
***
<br />

## Set G

Set LED green color pwm. <br />
  `RGB1` means RGB1 port 1. (Options: `RGB1` / `RGB2`)

```Arduino
void setG(uint8_t PWM)
```
### Parameters

- `PWM` is a **uint8_t** of green color. (Options: 0~255)
<br /><br /><br />
***
<br />

## Set B

Set LED blue color pwm. <br />
  `RGB1` means RGB1 port 1. (Options: `RGB1` / `RGB2`)

```Arduino
void setB(uint8_t PWM)
```
### Parameters

- `PWM` is a **uint8_t** of blue color. (Options: 0~255)
<br /><br /><br />
***
<br />

## Set RGB

Set LED RGB color pwm. <br />
  `RGB1` means RGB1 port 1. (Options: `RGB1` / `RGB2`)

```Arduino
void setHSV(int H, float S, float V)
```
### Parameters

- `H` is a **int** of hue.
- `S` is a **float** of saturation.
- `V` is a **float** of value.
<br /><br /><br />
***
<br />

## Set HSV

Set LED HSV color pwm. <br />
  `RGB1` means RGB1 port 1. (Options: `RGB1` / `RGB2`)

```Arduino
void setRGB(uint8_t PWMR, uint8_t PWMG, uint8_t PWMB)
```
### Parameters

- `H` is a **uint8_t** of red color. (Options: 0~255)
- `S` is a **uint8_t** of green color. (Options: 0~255)
- `V` is a **uint8_t** of blue color. (Options: 0~255)
<br /><br /><br />
***
<br />
