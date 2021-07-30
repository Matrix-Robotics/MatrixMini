## Analog 
### Get ANG

Get analog data from analog port. <br />
  `A1` means analog port 1. (Options: `A1` / `A2` / `A3`)

```Arduino
Mini.A1.getANG();
```
#### Return
- A **uint16_t** result of analog data.
<br />
***

### Get DIG

Get digital data from analog port. <br />
  `A1` means analog port 1. (Options: `A1` / `A2` / `A3`)

```Arduino
Mini.A1.getDIG();
```

#### Return

- A **boolean** result of digital data. (`true` / `false`)
<br /><br /><br />
***
<br />

## Button
### Get BTN

Get Button is clicked or not. <br />
  `BTN1` means Button 1. (Options: `BTN1` / `BTN2`)

```Arduino
Mini.BTN1.get();
```

#### Return

- A **boolean** result of BTN is clicked. (`true` / `false`)
<br /><br /><br />
***
<br />

## Digital
### Get DIG

Get digital data from digital port. <br />
  `D1` means digital port 1. (Options: `D1` / `D2` / `D3` / `D4`)

```Arduino
Mini.D1.get();
```

#### Return

- A **boolean** result of digital data. (`true` / `false`)
<br />
***

### Set DIG

Set digital data to digital port. <br />
  `D1` means digital port 1. (Options: `D1` / `D2` / `D3` / `D4`)

```Arduino
Mini.D1.set(byte);
```

#### Parameters

- `byte` is a **byte** which you want to set.
<br /><br /><br />
***
<br />

## Ultrasonic Sensor

## Get DIG

Get digital data from digital port by using ultrasonic sensor. <br />
  `D1` means digital port 1. (Options: `D1` / `D2` / `D3` / `D4`)

```Arduino
Mini.D1.US.get();
```

#### Return

- A **float**  distance of ultrasonic sensor and object.
<br /><br /><br />
***
<br />

## DC Motor

### Set Motor

Set DC Motor speed. <br />
  `M1` means Motor port 1. (Options: `M1` / `M2`)

```Arduino
Mini.M1.set(speed);
```
#### Parameters

- `speed` is a **int** of motor speed. (Options: 0~100)
<br /><br /><br />
***
<br />

## RC Motor

### Set RC

Set RC Servo angle. <br />
  `RC1` means RC port 1. (Options: `RC1` / `RC2` / `RC3` / `RC4`)

```Arduino
Mini.RC1.set(angle);
```
#### Parameters

- `angle` is a **int** of servo angle. (Options: 0~180)
<br /><br /><br />
***
<br />

## LED

### Set R

Set LED red color pwm. <br />
  `RGB1` means RGB1 port 1. (Options: `RGB1` / `RGB2`)

```Arduino
Mini.RGB1.setR(PWM);
```
#### Parameters

- `PWM` is a **uint8_t** of red color. (Options: 0~255)
<br />
***

### Set G

Set LED green color pwm. <br />
  `RGB1` means RGB1 port 1. (Options: `RGB1` / `RGB2`)

```Arduino
Mini.RGB1.setG(PWM);
```
#### Parameters

- `PWM` is a **uint8_t** of green color. (Options: 0~255)
<br />
***

### Set B

Set LED blue color pwm. <br />
  `RGB1` means RGB1 port 1. (Options: `RGB1` / `RGB2`)

```Arduino
Mini.RGB1.setB(PWM);
```
#### Parameters

- `PWM` is a **uint8_t** of blue color. (Options: 0~255)
<br />
***

### Set RGB

Set LED RGB color pwm. <br />
  `RGB1` means RGB1 port 1. (Options: `RGB1` / `RGB2`)

```Arduino
Mini.RGB1.setRGB(PWMR, PWMG, PWMB);
```
#### Parameters

- `PWMR` is a **uint8_t** of red color. (Options: 0~255)
- `PWMG` is a **uint8_t** of green color. (Options: 0~255)
- `PWMB` is a **uint8_t** of blue color. (Options: 0~255)
<br />
***

### Set HSV

Set LED HSV color pwm. <br />
  `RGB1` means RGB1 port 1. (Options: `RGB1` / `RGB2`)

```Arduino
Mini.RGB1.setHSV(H, S, V);
```
#### Parameters

- `H` is a **int** of hue.
- `S` is a **float** of saturation.
- `V` is a **float** of value.
