## Begin

Reset and initialize PS2 Controller to default state.

```Arduino
bool begin()
```
### Return

- A **boolean** result of initialization. (`true` / `false`)
<br /><br /><br />
***
<br />

## Polling

Polling data from PS2 Controller.

```Arduino
void polling()
```
### RX

- `L1` is a **boolean** of PS2 L1 button is clicked.
- `R1` is a **boolean** of PS2 R1 button is clicked.
- `L2` is a **boolean** of PS2 L2 button is clicked.
- `R2` is a **boolean** of PS2 R2 button is clicked.
- `L3` is a **boolean** of PS2 L3 button is clicked.
- `R3` is a **boolean** of PS2 R3 button is clicked.

- `SELECT` is a **boolean** of PS2 SELECT button is clicked.
- `START` is a **boolean** of PS2 START button is clicked.

- `UP` is a **boolean** of PS2 UP button is clicked.
- `RIGHT` is a **boolean** of PS2 RIGHT button is clicked.
- `DOWN` is a **boolean** of PS2 DOWN button is clicked.
- `LEFT` is a **boolean** of PS2 LEFT button is clicked.

- `TRIANGLE` is a **boolean** of PS2 TRIANGLE button is clicked.
- `CIRCLE` is a **boolean** of PS2 CIRCLE button is clicked.
- `CROSS` is a **boolean** of PS2 CROSS button is clicked.
- `SQUARE` is a **boolean** of PS2 SQUARE button is clicked.

- `RX` is a **uint8_t** of PS2 Right joystck X axis data.
- `RY` is a **uint8_t** of PS2 Right joystck Y axis data.
- `LX` is a **uint8_t** of PS2 Left joystck X axis data.
- `LY` is a **uint8_t** of PS2 Left joystck Y axis data.

<br /><br /><br />
***
<br />
