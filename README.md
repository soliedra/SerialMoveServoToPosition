#SerialMoveServoToPosition

Controls the position of a [DCMotorServo] (https://github.com/soliedra/DCMotorServo).

The target position is received through the Serial Port 

##Libraries used:
---------------
- [DCMotorServo] (https://github.com/soliedra/DCMotorServo) from julester23 modified by Javier Casado
- [MotorDriver] (https://github.com/soliedra/MotorDriver) from Javier Casado
- [VNH519MotorDriver] (https://github.com/soliedra/VNH5019MotorDriver) implementaion of MotorDriver for the Pololu VNH519 driver from Javier Casado
- [Encoder](http://www.pjrc.com/teensy/td_libs_Encoder.html) to measure the feedback from the Servo quadrature encoders
- [PID] (http://playground.arduino.cc/Code/PIDLibrary) to control the servo using a PID 

##Hardware:
--------
- [Arduino Mini](https://www.arduino.cc/en/Main/ArduinoBoardMini) V3.0 Atmega 328P as the microcontroller.
- [Pololu VNH519 Motor driver](https://www.pololu.com/product/1451) to drive the DC Motor
- [Pololu QTR-1RC] (https://www.pololu.com/product/2459) to make a DIY Quad encoder
- A 12V geared DC motor from a battery drill. Output speed approx 600rpm.
- 12V 7000mAh Lead battery. This DIY Servo Motor needs 34Ams for a split of a second to start moving big loads. In normal opration it consumes 2Amps.But the initial stroke is important.

Connections:
------------
VNH519MotorDriver:

<table>
<tr><td>Function</td><td>Pin</td><td>Arduino Pin</td></tr>
<tr><td>Direction CW</td><td>INA</td><td>D5</td></tr>
<tr><td>Direction CCW</td><td>INB</td><td>D7</td></tr>
<tr><td>Speed (0-255)</td><td>PWM</td><td>D6</td></tr>
</table>

Brake: INA and INB set to HIGH

QTR-1RC sensors:

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



