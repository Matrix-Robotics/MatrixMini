### Begin

Reset and initialize Matrix Mini Controller to default state.

```Arduino
Mini.begin(float vbat, bool _enUART, long buad);
```

#### Parameters

- `vbat` is a string of battery voltage.<br />
    `AA_6` means 6 AA batteries.<br />
    `LI_2` means 2 Li-ion batteries.  
    (Options: `AA_6` / `LI_2` / `LI_3` / `LI_4` / `LI_5` / `LI_6`)
- `_enUART` is a string of enable UART for serial control. (Options: `enable` / `disable`)
- `buad` is a  long int of UART baud rate. <br />
    (Options: `300` / `600` / `1200` / `2400` / `4800` / `9600` / `14400` / `19200` / `28800` / `31250` / `38400` / `57600` / `115200`)
