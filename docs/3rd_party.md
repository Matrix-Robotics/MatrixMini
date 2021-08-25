## PS2controller
### Begin
Reset and initialize PS2 Controller to default state.
```Arduino
Mini.PS2.begin();
```
#### Return

- A **boolean** result of initialization. (`true` / `false`)
<br />


### Polling

Polling data from PS2 Controller.
```Arduino
Mini.PS2.polling();
```
#### Object
- `Mini.PS2.L1` is a **boolean** of PS2 L1 button is clicked.
- `Mini.PS2.R1` is a **boolean** of PS2 R1 button is clicked.
- `Mini.PS2.L2` is a **boolean** of PS2 L2 button is clicked.
- `Mini.PS2.R2` is a **boolean** of PS2 R2 button is clicked.
- `Mini.PS2.L3` is a **boolean** of PS2 L3 button is clicked.
- `Mini.PS2.R3` is a **boolean** of PS2 R3 button is clicked.
- `Mini.PS2.SELECT` is a **boolean** of PS2 SELECT button is clicked.
- `Mini.PS2.START` is a **boolean** of PS2 START button is clicked.
- `Mini.PS2.UP` is a **boolean** of PS2 UP button is clicked.
- `Mini.PS2.RIGHT` is a **boolean** of PS2 RIGHT button is clicked.
- `Mini.PS2.DOWN` is a **boolean** of PS2 DOWN button is clicked.
- `Mini.PS2.LEFT` is a **boolean** of PS2 LEFT button is clicked.
- `Mini.PS2.TRIANGLE` is a **boolean** of PS2 TRIANGLE button is clicked.
- `Mini.PS2.CIRCLE` is a **boolean** of PS2 CIRCLE button is clicked.
- `Mini.PS2.CROSS` is a **boolean** of PS2 CROSS button is clicked.
- `Mini.PS2.SQUARE` is a **boolean** of PS2 SQUARE button is clicked.
- `Mini.PS2.RX` is a **uint8_t** of PS2 Right joystck X axis data.
- `Mini.PS2.RY` is a **uint8_t** of PS2 Right joystck Y axis data.
- `Mini.PS2.LX` is a **uint8_t** of PS2 Left joystck X axis data.
- `Mini.PS2.LY` is a **uint8_t** of PS2 Left joystck Y axis data.