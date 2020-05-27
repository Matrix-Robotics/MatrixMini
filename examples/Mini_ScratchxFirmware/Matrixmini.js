/*
Last Update: 09/06/2018
JS Version: 1.14
Author: Ning Yu
*/
(function(ext) {

  var MINI_DCMOTOR_CONFIG = 0x04,
    MINI_SERVO_CONFIG = 0x08,
    MINI_RGB_CONFIG = 0x12,
    MINI_BTN_REPORT = 0x0B,
    MINI_GET_ULTRA = 0x10;

  var PIN_MODE = 0xF4,
    REPORT_DIGITAL = 0xD0,
    REPORT_ANALOG = 0xC0,
    DIGITAL_MESSAGE = 0x90,
    START_SYSEX = 0xF0,
    END_SYSEX = 0xF7,
    QUERY_FIRMWARE = 0x79,
    REPORT_VERSION = 0xF9,
    ANALOG_MESSAGE = 0xE0,
    ANALOG_MAPPING_QUERY = 0x69,
    ANALOG_MAPPING_RESPONSE = 0x6A,
    CAPABILITY_QUERY = 0x6B,
    CAPABILITY_RESPONSE = 0x6C;

  var INPUT = 0x00,
    OUTPUT = 0x01,
    ANALOG = 0x02,
    PWM = 0x03,
    SERVO = 0x04,
    SHIFT = 0x05,
    I2C = 0x06,
    ONEWIRE = 0x07,
    STEPPER = 0x08,
    ENCODER = 0x09,
    SERIAL = 0x0A,
    PULLUP = 0x0B,
    IGNORE = 0x7F,
    TOTAL_PIN_MODES = 13;

  var LOW = 0,
    HIGH = 1;

  var MAX_DATA_BYTES = 4096;
  var MAX_PINS = 128;

  var parsingSysex = false,
    waitForData = 0,
    executeMultiByteCommand = 0,
    multiByteChannel = 0,
    sysexBytesRead = 0,
    storedInputData = new Uint8Array(MAX_DATA_BYTES);

  var MINI_BTN_Status = [];
  //var mini_digitalPortInputData = new Uint16Array(16);
  var RangeInCentimeters = 0;

  var digitalOutputData = new Uint8Array(16),
    digitalInputData = new Uint8Array(16),
    analogInputData = new Uint16Array(16);

  var analogChannel = new Uint8Array(MAX_PINS);
  var pinModes = [];
  for (var i = 0; i < TOTAL_PIN_MODES; i++) pinModes[i] = [];

  var majorVersion = 0,
    minorVersion = 0;

  var connected = false;
  var notifyConnection = false;
  var device = null;
  var inputData = null;

  // TEMPORARY WORKAROUND
  // Since _deviceRemoved is not used with Serial devices
  // ping device regularly to check connection
  var pinging = false;
  var pingCount = 0;
  var pinger = null;

  var hwList = new HWList();

  function HWList() {
    this.devices = [];

    this.add = function(dev, pin) {
      var device = this.search(dev);
      if (!device) {
        device = {name: dev, pin: pin, val: 0};
        this.devices.push(device);
      } else {
        device.pin = pin;
        device.val = 0;
      }
    };

    this.search = function(dev) {
      for (var i=0; i<this.devices.length; i++) {
        if (this.devices[i].name === dev)
          return this.devices[i];
      }
      return null;
    };
  }

  function init() {

    for (var i = 0; i < 16; i++) {
      var output = new Uint8Array([REPORT_DIGITAL | i, 0x01]);
      device.send(output.buffer);
    }

    queryCapabilities();

    // TEMPORARY WORKAROUND
    // Since _deviceRemoved is not used with Serial devices
    // ping device regularly to check connection
    pinger = setInterval(function() {
      if (pinging) {
        if (++pingCount > 6) {
          clearInterval(pinger);
          pinger = null;
          connected = false;
          if (device) device.close();
          device = null;
          return;
        }
      } else {
        if (!device) {
          clearInterval(pinger);
          pinger = null;
          return;
        }
        queryFirmware();
        pinging = true;
      }
    }, 100);
  }

  function hasCapability(pin, mode) {
    if (pinModes[mode].indexOf(pin) > -1)
      return true;
    else
      return false;
  }

  function queryFirmware() {
    var output = new Uint8Array([START_SYSEX, QUERY_FIRMWARE, END_SYSEX]);
    device.send(output.buffer);
  }

  function queryCapabilities() {
    console.log('Querying ' + device.id + ' capabilities');
    var msg = new Uint8Array([
        START_SYSEX, CAPABILITY_QUERY, END_SYSEX]);
    device.send(msg.buffer);
  }

  function queryAnalogMapping() {
    console.log('Querying ' + device.id + ' analog mapping');
    var msg = new Uint8Array([
        START_SYSEX, ANALOG_MAPPING_QUERY, END_SYSEX]);
    device.send(msg.buffer);
  }
  function setminiDigitalPortInputs(portNum, portData) {
    mini_digitalPortInputData[portNum] = portData;
  }
  function setDigitalInputs(portNum, portData) {
    digitalInputData[portNum] = portData;
  }

  function setAnalogInput(pin, val) {
    analogInputData[pin] = val;
  }

  function setVersion(major, minor) {
    majorVersion = major;
    minorVersion = minor;
  }

  function processSysexMessage() {
    switch(storedInputData[0]) {
      case CAPABILITY_RESPONSE:
        for (var i = 1, pin = 0; pin < MAX_PINS; pin++) {
          while (storedInputData[i++] != 0x7F) {
            pinModes[storedInputData[i-1]].push(pin);
            i++; //Skip mode resolution
          }
          if (i == sysexBytesRead) break;
        }
        queryAnalogMapping();
        break;
      case ANALOG_MAPPING_RESPONSE:
        for (var pin = 0; pin < analogChannel.length; pin++)
          analogChannel[pin] = 127;
        for (var i = 1; i < sysexBytesRead; i++)
          analogChannel[i-1] = storedInputData[i];
        for (var pin = 0; pin < analogChannel.length; pin++) {
          if (analogChannel[pin] != 127) {
            var out = new Uint8Array([
                REPORT_ANALOG | analogChannel[pin], 0x01]);
            device.send(out.buffer);
          }
        }
        notifyConnection = true;
        setTimeout(function() {
          notifyConnection = false;
        }, 100);
        break;
      case QUERY_FIRMWARE:
        if (!connected) {
          clearInterval(poller);
          poller = null;
          clearTimeout(watchdog);
          watchdog = null;
          connected = true;
          setTimeout(init, 200);
        }
        pinging = false;
        pingCount = 0;
        break;

      case MINI_BTN_REPORT:
        //console.log('BTN command recieved');
        if(storedInputData[1]==8)
          MINI_BTN_Status[1] = storedInputData[2];
        else if(storedInputData[1]==7)
          MINI_BTN_Status[2] = storedInputData[2];
        sysexBytesRead = 0;
        break;

      case MINI_GET_ULTRA:
        console.log('ultrasonic command recieved ',sysexBytesRead);
        RangeInCentimeters = storedInputData[1] + (storedInputData[2] << 8 );
        sysexBytesRead = 0;
        break;
    }
  }

  function processInput(inputData) {
    for (var i=0; i < inputData.length; i++) {
      if (parsingSysex) {
        if (inputData[i] == END_SYSEX) {
          parsingSysex = false;
          processSysexMessage();
        } else {
          storedInputData[sysexBytesRead++] = inputData[i];
        }
      } else if (waitForData > 0 && inputData[i] < 0x80) {
        storedInputData[--waitForData] = inputData[i];
        if (executeMultiByteCommand !== 0 && waitForData === 0) {
          switch(executeMultiByteCommand) {
            case DIGITAL_MESSAGE:
              setDigitalInputs(multiByteChannel, (storedInputData[0] << 7) + storedInputData[1]);
              break;
            case ANALOG_MESSAGE:
              setAnalogInput(multiByteChannel, (storedInputData[0] << 7) + storedInputData[1]);
              break;
            case REPORT_VERSION:
              setVersion(storedInputData[1], storedInputData[0]);
              break;
          }
        }
      } else {
        if (inputData[i] < 0xF0) {
          command = inputData[i] & 0xF0;
          multiByteChannel = inputData[i] & 0x0F;
        } else {
          command = inputData[i];
        }
        switch(command) {
          case DIGITAL_MESSAGE:
          case ANALOG_MESSAGE:
          case REPORT_VERSION:
            waitForData = 2;
            executeMultiByteCommand = command;
            break;
          case START_SYSEX:
            parsingSysex = true;
            sysexBytesRead = 0;
            break;
        }
      }
    }
  }

/*****************************************************************************
                        Arduino Firmata protocols
*****************************************************************************/
  function pinMode(pin, mode) {
    var msg = new Uint8Array([PIN_MODE, pin, mode]);
    device.send(msg.buffer);
  }

  function analogRead(pin) {
    switch(pin){
        case menus[lang]['mini_analog_pins'][0]:
          pin = 0;
          break;
        case menus[lang]['mini_analog_pins'][1]:
          pin = 1;
          break;
        case menus[lang]['mini_analog_pins'][2]:
          pin = 2;
          break;
        case menus[lang]['mini_analog_pins'][3]:
          pin = 3;
          break;
    }
    if (pin >= 0 && pin < pinModes[ANALOG].length) {
      return Math.round((analogInputData[pin] * 100) / 1023);
    } else {
      var valid = [];
      for (var i = 0; i < pinModes[ANALOG].length; i++)
        valid.push(i);
      console.log('ERROR: valid analog pins are ' + valid.join(', '));
      return;
    }
  }

  function digitalRead(pin) {
    switch(pin){
        case menus[lang]['mini_digital_pins'][0]:
          pin = 2;
          break;
        case menus[lang]['mini_digital_pins'][1]:
          pin = 3;
          break;
        case menus[lang]['mini_digital_pins'][2]:
          pin = 4;
          break;
        case menus[lang]['mini_digital_pins'][3]:
          pin = 5;
          break;
        case menus[lang]['mini_digital_pins'][4]:
          pin = 6;
          break;
    }
    if (!hasCapability(pin, INPUT)) {
      console.log('ERROR: valid input pins are ' + pinModes[INPUT].join(', '));
      return;
    }
    pinMode(pin, INPUT);
    return (digitalInputData[pin >> 3] >> (pin & 0x07)) & 0x01;
  }

  function analogWrite(pin, val) {
    switch(pin){
        case menus[lang]['mini_analog_pins'][0]:
          pin = 0;
          break;
        case menus[lang]['mini_analog_pins'][1]:
          pin = 1;
          break;
        case menus[lang]['mini_analog_pins'][2]:
          pin = 2;
          break;
        case menus[lang]['mini_analog_pins'][3]:
          pin = 3;
          break;
    }
    if (!hasCapability(pin, PWM)) {
      console.log('ERROR: valid PWM pins are ' + pinModes[PWM].join(', '));
      return;
    }
    if (val < 0) val = 0;
    else if (val > 100) val = 100;
    val = Math.round((val / 100) * 255);
    pinMode(pin, PWM);
    var msg = new Uint8Array([
        ANALOG_MESSAGE | (pin & 0x0F),
        val & 0x7F,
        val >> 7]);
    device.send(msg.buffer);
  }

  function digitalWrite(pin, val) {
    switch(pin) {
        case menus[lang]['mini_digital_pins'][0]:
          pin = 2;
          break;
        case menus[lang]['mini_digital_pins'][1]:
          pin = 3;
          break;
        case menus[lang]['mini_digital_pins'][2]:
          pin = 4;
          break;
        case menus[lang]['mini_digital_pins'][3]:
          pin = 5;
          break;
        case menus[lang]['mini_digital_pins'][4]:
          pin = 6;
          break;
    }
    if (!hasCapability(pin, OUTPUT)) {
      console.log('ERROR: valid output pins are ' + pinModes[OUTPUT].join(', '));
      return;
    }
    var portNum = (pin >> 3) & 0x0F;
    if (val == LOW)
      digitalOutputData[portNum] &= ~(1 << (pin & 0x07));
    else
      digitalOutputData[portNum] |= (1 << (pin & 0x07));
    pinMode(pin, OUTPUT);
    var msg = new Uint8Array([
        DIGITAL_MESSAGE | portNum,
        digitalOutputData[portNum] & 0x7F,
        digitalOutputData[portNum] >> 0x07]);
    device.send(msg.buffer);
  }

  /*****************************************************************************
                          Matrixmini Standard protocols
  *****************************************************************************/
  ext.SetMiniDCMotorSpeed = function(num, speed) {
    var clockwise;
    if(num > 2) {
      console.log('ERROR: invalid mini motor port');
      return;
    }

    if(speed >= 0){
      if(speed >=100) speed = 100;
      clockwise = 0;
    }
    else {
      if(speed <=-100) speed = -100;
      clockwise = 1;
      speed = -speed;
    }

    var msg = new Uint8Array([
        START_SYSEX,
        MINI_DCMOTOR_CONFIG,
        num,
        clockwise,
        speed,
        END_SYSEX]);
    device.send(msg.buffer);
    console.log('Set DC Motor Speed = ',speed);
  };

  ext.SetMiniServoDegree = function(num,deg) {
    if(num > 4) {
      console.log('ERROR: invalid mini servo port');
      return;
    }

    if(deg < 0) deg = 0;
    if(deg >180) deg = 180;

    var msg = new Uint8Array([
        START_SYSEX,
        MINI_SERVO_CONFIG,
        num,
        deg & 0x7F,
        deg >> 0x07,
        END_SYSEX]);
    device.send(msg.buffer);
    console.log('Set Servo Degree');
  };

  ext.SetMiniRGBPwm = function(num,valR,valG,valB) {
    if(num > 2) {
      console.log('ERROR: invalid mini RGB port');
      return;
    }

    if(valR > 255) ValR = 255;
    if(valR < 0)   ValR = 0;

    if(valG > 255) valG = 255;
    if(valG < 0)   valG = 0;

    if(valB > 255) valB = 255;
    if(valB < 0)   valB = 0;

    var msg = new Uint8Array([
        START_SYSEX,
        MINI_RGB_CONFIG,
        num,
        valR & 0x7F,
        valR >> 0x07,
        valG & 0x7F,
        valG >> 0x07,
        valB & 0x7F,
        valB >> 0x07,
        END_SYSEX]);
    device.send(msg.buffer);
    console.log('Set RGB Pwm Value');
  };

  ext.ReadMiniButton = function(hw) {
    var pin;
    var led_num;
    if(hw == menus[lang]['mini_buttons'][0]) {
      pin = 8;
      led_num = 1;
      //console.log('MINI_BTN_Status 1 =' + MINI_BTN_Status[1]);
    }
    else if (hw == menus[lang]['mini_buttons'][1]) {
      pin = 7;
      led_num = 2;
      //console.log('MINI_BTN_Status 2 =' + MINI_BTN_Status[2]);
    }
    else {
      console.log('ERROR: invalid mini Button port');
      return;
    }

    var msg = new Uint8Array([
        START_SYSEX,
        MINI_BTN_REPORT,
        pin,
        END_SYSEX]);
    device.send(msg.buffer);

    //console.log('MINI_BTN_Status =' + MINI_BTN_Status);
    return (MINI_BTN_Status[led_num]==1)?true:false;
  };

  ext.getUltrasonic = function(hw) {
    var digitalPort;
    //ultrasonic sensor with echo and trig pins
    if(hw == menus[lang]['mini_digitalPorts'][0]) {
      digitalPort = 1;
    }
    else if (hw == menus[lang]['mini_buttons'][1]) {
      digitalPort = 2;
    }
    else if (hw == menus[lang]['mini_buttons'][2]) {
      digitalPort = 3;
    }
    else if (hw == menus[lang]['mini_buttons'][3]) {
      digitalPort = 4;
    }

    var msg = new Uint8Array([
        START_SYSEX,
        MINI_GET_ULTRA,
        digitalPort,
        END_SYSEX]);
    device.send(msg.buffer);
    console.log('Range in cm =' + RangeInCentimeters);
    return RangeInCentimeters;
  };
  /*****************************************************************************

  *****************************************************************************/

  ext.whenConnected = function() {
    if (notifyConnection) return true;
    return false;
  };

  ext.analogWrite = function(pin, val) {
    analogWrite(pin, val);
  };

  ext.digitalWrite = function(pin, val) {
    if (val == menus[lang]['outputs'][0])
      digitalWrite(pin, HIGH);
    else if (val == menus[lang]['outputs'][1])
      digitalWrite(pin, LOW);
  };

  ext.analogRead = function(pin) {
    return analogRead(pin);
  };

  ext.digitalRead = function(pin) {
    return digitalRead(pin);
  };

  ext.whenAnalogRead = function(pin, op, val) {
    if (pin >= 0 && pin < pinModes[ANALOG].length) {
      if (op == '>')
        return analogRead(pin) > val;
      else if (op == '<')
        return analogRead(pin) < val;
      else if (op == '=')
        return analogRead(pin) == val;
      else
        return false;
    }
  };

  ext.whenDigitalRead = function(pin, val) {
    if (hasCapability(pin, INPUT)) {
      if (val == menus[lang]['outputs'][0])
        return digitalRead(pin);
      else if (val == menus[lang]['outputs'][1])
        return digitalRead(pin) === false;
    }
  };

  ext.connectHW = function(hw, pin) {
    hwList.add(hw, pin);
  };

  ext.readInput = function(name) {
    var hw = hwList.search(name);
    if (!hw) return;
    return analogRead(hw.pin);
  };

////////////////////
  ext.whenInput = function(name, op, val) {
    var hw = hwList.search(name);
    if (!hw) return;
    if (op == '>')
      return analogRead(hw.pin) > val;
    else if (op == '<')
      return analogRead(hw.pin) < val;
    else if (op == '=')
      return analogRead(hw.pin) == val;
    else
      return false;
  };

  ext.mapValues = function(val, aMin, aMax, bMin, bMax) {
    var output = (((bMax - bMin) * (val - aMin)) / (aMax - aMin)) + bMin;
    return Math.round(output);
  };

  ext._getStatus = function() {
    if (!connected)
      return { status:1, msg:'Disconnected' };
    else
      return { status:2, msg:'Connected' };
  };

  ext._deviceRemoved = function(dev) {
    console.log('Device removed');
    // Not currently implemented with serial devices
  };

  var potentialDevices = [];
  ext._deviceConnected = function(dev) {
    potentialDevices.push(dev);
    if (!device)
      tryNextDevice();
  };

  var poller = null;
  var watchdog = null;
  function tryNextDevice() {
    device = potentialDevices.shift();
    if (!device) return;

    device.open({ stopBits: 0, bitRate: 9600, ctsFlowControl: 0 });
    console.log('Attempting connection with ' + device.id);
    device.set_receive_handler(function(data) {
      var inputData = new Uint8Array(data);
      processInput(inputData);
    });

    poller = setInterval(function() {
      queryFirmware();
    }, 1000);

    watchdog = setTimeout(function() {
      clearInterval(poller);
      poller = null;
      device.set_receive_handler(null);
      device.close();
      device = null;
      tryNextDevice();
    }, 5000);
  }

  ext._shutdown = function() {
    // TODO: Bring all pins down
    if (device) device.close();
    if (poller) clearInterval(poller);
    device = null;
  };

  // Check for GET param 'lang'
  var paramString = window.location.search.replace(/^\?|\/$/g, '');
  var vars = paramString.split("&");
  var lang = 'en';
  for (var i=0; i<vars.length; i++) {
    var pair = vars[i].split('=');
    if (pair.length > 1 && pair[0]=='lang')
      lang = pair[1];
  }

  var blocks = {
    en: [
      //Matrixmini extensions
      ['h', 'when mini is connected', 'whenConnected'],
      ['-'],//mini supported functions
      [' ', 'Set mini DCMotor %m.minimotorPort speed %n', 'SetMiniDCMotorSpeed', '1', 100],
      [' ', 'set mini servo %m.miniservoPort angle %n' ,'SetMiniServoDegree', '1', 90],
      [' ', 'set mini rgb %m.minirgbPort R %n G %n B %n' ,'SetMiniRGBPwm', '1', 0, 0, 0],
      ['b', 'is mini Button %m.mini_buttons pressed?', 'ReadMiniButton', 'MINI_BTN1'],
      ['-'],//sensors//ports
      ['r', 'Measure Ultrasonic Distance on Digital Port %m.mini_digitalPorts In Centimeters', 'getUltrasonic','D1'],
      ['-'],//digital pins
      ['h', 'when digital pin %m.mini_digital_pins is %m.outputs', 'whenDigitalRead', 'd1', 'on'],
      [' ', 'set digital pin %m.mini_digital_pins %m.outputs', 'digitalWrite', 'd1', 'on'],
      ['b', 'is digital pin %m.mini_digital_pins on?', 'digitalRead', 'd1'],
      ['-'],//analog pins
      ['h', 'when analog %n %m.ops %n%', 'whenAnalogRead', 1, '>', 50],
      [' ', 'set analog pin %m.mini_analog_pins to %n', 'analogWrite', 'a0', 100],
      ['r', 'read analog pin %m.mini_analog_pins', 'analogRead', 'a0'],
      ['-'],//caculations
      ['r', 'map %n from %n %n to %n %n', 'mapValues', 50, 0, 100, -255, 255]
    ],
    zh: [
      ['h', '當 mini 連接時', 'whenConnected'],
      ['-'],//mini支援的功能
      [' ', '設定 mini 馬達 %m.minimotorPort 轉速為 %n', 'SetMiniDCMotorSpeed','1', 100],
      [' ', '旋轉 mini 伺服馬達 %m.miniservoPort 到 %n 度', 'SetMiniServoDegree', '1', 90],
      [' ', '設定 mini RGB %m.minirgbPort 的亮度為 紅色 %n 綠色 %n 藍色 %n', 'SetMiniRGBPwm', '1',0, 0, 0],
      ['b', '偵測到 %m.mini_buttons 被按下?', 'ReadMiniButton', 'MINI按鈕 1'],
      ['-'],//感測器
      ['r', '設定數位插座 %m.mini_digitalPorts 並量測超音波距離(公分)', 'getUltrasonic','D1'],
      ['-'],//數位腳位
      ['h', '當數位腳位 %m.mini_digital_pins 為 %m.outputs', 'whenDigitalRead', 'd1', '開'],
      [' ', '設定數位腳位 %m.mini_digital_pins %m.outputs', 'digitalWrite', 'd1', '開'],
      ['b', '偵測到數位腳位 %m.mini_digital_pins 為 1?', 'digitalRead', 'd1'],
      ['-'],//類比腳位
      ['h', '當類比 %n %m.ops %n%', 'whenAnalogRead', 1, '>', 50],
      [' ', '設定類比腳位 %m.mini_analog_pins 為 %n', 'analogWrite', 'a0', 100],
      ['r', '讀取類比角為 %m.mini_analog_pins', 'analogRead', 'a0'],
      ['-'],//計算方程式
      ['r', '對應 %n 由 %n %n 為 %n %n', 'mapValues', 50, 0, 100, -255, 255]
    ]
  };

  var menus = {
    en: {
      buttons: ['button A', 'button B', 'button C', 'button D'],
      btnStates: ['pressed', 'released'],
      hwIn: ['rotation knob', 'light sensor', 'temperature sensor'],
      hwOut: ['led A', 'led B', 'led C', 'led D', 'button A', 'button B', 'button C', 'button D', 'servo A', 'servo B', 'servo C', 'servo D'],
      leds: ['led A', 'led B', 'led C', 'led D'],
      outputs: ['on', 'off'],
      ops: ['>', '=', '<'],
      servos: ['servo A', 'servo B', 'servo C', 'servo D'],

//Matrixmini menu////////////////////////////////////////////////
      minimotorPort:['1','2'],
      miniservoPort:['1','2','3','4'],
      minirgbPort:['1','2'],
      speed:['255','100','50','0','-50','-100','-255'],
      rgbvalue:['0','50','100','150','200','255'],
      servovalue:['0','45','90','135','180'],
      mini_buttons: ['MINI_BTN1', 'MINI_BTN2'],
      mini_digital_pins: ['d1','d2','d3','d4','d5'],
      mini_analog_pins: ['a0','a1','a2','a3'],
      mini_digitalPorts: ['D1','D2','D3','D4'],
      mini_analogPorts: ['A1','A2','A3']
//////////////////////////////////////////////////////////////////
    },
    zh: {
      buttons: ['按鈕 A', '按鈕 B', '按鈕 C', '按鈕 D'],
      btnStates: ['按下', '放開'],
      hwIn: ['旋鈕', '光感應器', '溫度感應器'],
      hwOut: ['發光二極體 A', '發光二極體 B', '發光二極體 C', '發光二極體 D', '按鈕 A', '按鈕 B', '按鈕 C', '按鈕 D', '伺服馬達 A', '伺服馬達 B', '伺服馬達 C', '伺服馬達 D'],
      leds: ['發光二極體 A', '發光二極體 B', '發光二極體 C', '發光二極體 D'],
      outputs: ['開', '關'],
      ops: ['>', '=', '<'],
      servos: ['伺服馬達 A', '伺服馬達 B', '伺服馬達 C', '伺服馬達 D'],
      mini_buttons: ['MINI按鈕 1', 'MINI按鈕 2']
    }
  };

  var descriptor = {
    blocks: blocks[lang],
    menus: menus[lang],
    url: 'http://khanning.github.io/scratch-arduino-extension'
  };

  ScratchExtensions.register('Matrixmini', descriptor, ext, {type:'serial'});

})({});
