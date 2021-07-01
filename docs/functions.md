## Set Angle

RC-servo angle setting.

```Arduino
void setAngle(int ch, uint8_t Angle)
```

### Parameters

- `ch` is a channel number from `1` through `8`
- `Angle` is a servo angle from `0` through `180` (unit: degree)
<br /><br /><br />
***
<br />

## Channel Release

Release the select servo.

```Arduino
void ChannelRelease(int ch)
```

### Parameters

- `ch` is a channel number from `1` through `8`
<br /><br /><br />
***
<br />

## Get Battery Voltage

Get battery **voltage** of controller.

```Arduino
float getVbat()
```

### Return

- A **float** number from `0` through `8.4`. (unit: v)




  Mini.A1.getANG();

  Mini.A1.getDIG();

  Mini.BTN1.get();

  Mini.D1.get();

  Mini.D1.set();

  Mini.D1.US.get();

  Mini.M1.set();

  Mini.RC1.set();

  Mini.RGB1.setR();
  
  Mini.RGB1.setG();
  
  Mini.RGB1.setB();
  
  Mini.RGB1.setRGB();

  Mini.RGB1.setHSV();
