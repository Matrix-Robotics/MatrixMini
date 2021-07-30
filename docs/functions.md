## Analog 
`AX` 's `X` means number of the analog port. (Options: `A1` / `A2` / `A3`)
### Get ANG

Get analog data from analog port. <br />
  

```Arduino
Mini.AX.getANG()
```
#### Return
- A **uint16_t** result of analog data.
<br />
***

### Get DIG

Get digital data from analog port. <br />

```Arduino
Mini.AX.getDIG()
```

#### Return

- A **boolean** result of digital data. (`true` / `false`)
<br /><br /><br />
***
<br />

## Button

`BTNX` 's `X` means number of the Button. (Options: `BTN1` / `BTN2`)

### Get BTN

Get Button is clicked or not. <br />

```Arduino
Mini.BTNX.get()
```

#### Return

- A **boolean** result of BTN is clicked. (`true` / `false`)
<br /><br /><br />
***
<br />

## Digital

`DX` 's `X` means number of the digital port. (Options: `D1` / `D2` / `D3` / `D4`)

### Get DIG

Get digital data from digital port. <br />

```Arduino
Mini.DX.get()
```

#### Return

- A **boolean** result of digital data. (`true` / `false`)
<br />
***

### Set DIG

Set digital data to digital port. <br />

```Arduino
Mini.DX.set(byte v);
```

#### Parameters

- `v` is a **byte** which you want to set.
<br /><br /><br />
***
<br />

## Ultrasonic Sensor

`DX` 's `X` means number of the digital port. (Options: `D1` / `D2` / `D3` / `D4`)

## Get DIG

Get digital data from digital port by using ultrasonic sensor. <br />

```Arduino
Mini.DX.US.get()
```

#### Return

- A **float**  distance of ultrasonic sensor and object.
<br /><br /><br />
***
<br />

## DC Motor

`MX` 's `X` means number of the Motor port. (Options: `M1` / `M2`)

### Set Motor

Set DC Motor speed. <br />

```Arduino
Mini.MX.set(int speed);
```
#### Parameters

- `speed` is a **int** of motor speed. (Options: 0~100)
<br /><br /><br />
***
<br />

## RC Motor

`RCX` 's `X` means number of the RC port. (Options: `RC1` / `RC2` / `RC3` / `RC4`)

### Set RC

Set RC Servo angle. <br />

```Arduino
Mini.RCX.set(int angle);
```
#### Parameters

- `angle` is a **int** of servo angle. (Options: 0~180)
<br /><br /><br />
***
<br />

## LED

`RGBX` 's `X` means number of the RGB port. (Options: `RGB1` / `RGB2`)

### Set R

Set LED red color pwm. <br />

```Arduino
Mini.RGBX.setR(uint8_t PWM);
```
#### Parameters

- `PWM` is a **uint8_t** of red color. (Options: 0~255)
<br />
***

### Set G

Set LED green color pwm. <br />

```Arduino
Mini.RGBX.setG(uint8_t PWM);
```
#### Parameters

- `PWM` is a **uint8_t** of green color. (Options: 0~255)
<br />
***

### Set B

Set LED blue color pwm. <br />

```Arduino
Mini.RGBX.setB(uint8_t PWM);
```
#### Parameters

- `PWM` is a **uint8_t** of blue color. (Options: 0~255)
<br />
***

### Set RGB

Set LED RGB color pwm. <br />

```Arduino
Mini.RGBX.setRGB(uint8_t PWMR, uint8_t PWMG, uint8_t PWMB);
```
#### Parameters

- `PWMR` is a **uint8_t** of red color. (Options: 0~255)
- `PWMG` is a **uint8_t** of green color. (Options: 0~255)
- `PWMB` is a **uint8_t** of blue color. (Options: 0~255)
<br />
***

### Set HSV

Set LED HSV color pwm. <br />

```Arduino
Mini.RGBX.setHSV(int H, float S, float V);
```
#### Parameters

- `H` is a **int** of hue.
- `S` is a **float** of saturation.
- `V` is a **float** of value.

