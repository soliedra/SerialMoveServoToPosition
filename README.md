#SerialMoveServoToPosition

Controls the position of a DIY Servo Motor [DCMotorServo] (https://github.com/soliedra/DCMotorServo).

The target position is received through the Serial Port 

It's important to understand that the Encoder library is based on interrupts and consumes a lot od CPU time.
Don't add more code in the main loop, keep it as efficient and smooth running as possible, otherwise you'll genereate unestable behavior in the Servo  Motor. 
Anything that has to do with timing such as AD conversion and delays doesn't work well in this sketch and will interfere with it's main duty, that is driving the servo
to the target position, nothing more, nothing less.
If you need more logic in your project, use another Arduino board to manage inputs, timings, user interface and
just send the position where you want the servomotor to move through the serial port as a number to the Arduino board that
runs this sketch.

##Libraries used:
- [DCMotorServo] (https://github.com/soliedra/DCMotorServo) from julester23 modified by Javier Casado
- [MotorDriver] (https://github.com/soliedra/MotorDriver) from Javier Casado
- [VNH519MotorDriver] (https://github.com/soliedra/VNH5019MotorDriver) implementaion of MotorDriver for the Pololu VNH519 driver from Javier Casado
- [Encoder](http://www.pjrc.com/teensy/td_libs_Encoder.html) to measure the feedback from the Servo quadrature encoders
- [PID] (http://playground.arduino.cc/Code/PIDLibrary) to control the servo using a PID 

##Hardware:
- [Arduino Mini](https://www.arduino.cc/en/Main/ArduinoBoardMini) V3.0 Atmega 328P as the microcontroller.
- [Pololu VNH519 Motor driver](https://www.pololu.com/product/1451) to drive the DC Motor
- [Pololu QTR-1RC] (https://www.pololu.com/product/2459) to make a DIY Quad encoder that can do 32 CPR in the output shaft (not the motor's)
- A 12V geared DC motor from a battery drill. Output speed approx 600rpm.
- 12V 7000mAh Lead battery. This DIY Servo Motor needs 34 Ams for a split of a second to start moving big loads. Under normal operation it consumes 2 Amps. But the initial stroke is important to reach the target position inmediately.

##Connections:
###VNH519MotorDriver:

<table>
<tr><td>Function</td><td>Pin</td><td>Arduino Pin</td></tr>
<tr><td>Direction CW</td><td>INA</td><td>D5</td></tr>
<tr><td>Direction CCW</td><td>INB</td><td>D7</td></tr>
<tr><td>Speed (0-255)</td><td>PWM</td><td>D6</td></tr>
</table>

Brake: INA and INB set to HIGH

###QTR-1RC sensors:

Front view of the Sensors location
```
        B
       ***
      *   * A
       ***
 CW(+)<---> CCW (-)
 

Encoder A -> D2 Arduino, external interrupt
Encoder B -> D3 Arduino, external interrupt


Activation sequence
                 ______        ______
  Encoder A  ___|      |______|      |______
                    ______        ______
  Encoder B  ______|      |______|      |______
             CCW-->(-)                   (+) <--CW

```
Created by Javier Casado July 2016

License: CC BY

### TO DO
- Add another Serial interface to configure the servomotor parameters through commands like AT commands.
- Store the config parameters, now harcoded in the EEPROM memory



