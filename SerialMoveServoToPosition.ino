/*
* Controls de position of a [DCMotorServo] (https://github.com/soliedra/DCMotorServo).
*
*The target position is received through the SerialPort 
*
*Libraries used:
*---------------
*-[DCMotorServo] (https://github.com/soliedra/DCMotorServo) from julester23 modified by Javier Casado
*-[MotorDriver] (https://github.com/soliedra/MotorDriver) from Javier Casado
*-[VNH519MotorDriver] (https://github.com/soliedra/VNH5019MotorDriver) implementaion of MotorDriver for the Pololu VNH519 driver from Javier Casado
*-[Encoder](http://www.pjrc.com/teensy/td_libs_Encoder.html) to measure the feedback from the Servo quadrature encoders
*-[PID] (http://playground.arduino.cc/Code/PIDLibrary) to control the servo using a PID 
*
*Hardware:
*--------
*- [Arduino Mini](https://www.arduino.cc/en/Main/ArduinoBoardMini) V3.0 Atmega 328P as the microcontroller.
*- [Pololu VNH519 Motor driver](https://www.pololu.com/product/1451) to drive the DC Motor
*- [Pololu QTR-1RC] (https://www.pololu.com/product/2459) to make a DIY Quad encoder
*- A 12V geared DC motor from a battery drill. Output speed approx 600rpm.
*- 12V 7000mAh Lead battery. This DIY Servo Motor needs 34Ams for a split of a second to start moving big loads. In normal opration it consumes 2Amps.But the initial stroke is important.
*
*Connections:
*------------
*
*VNH519MotorDriver:
*
*Function      |  Pin  | Arduino Pin | I/O
*------------------------------------------
*Direction CW  | INA   | D5          | I
*------------------------------------------
*Direction CCW | INB   | D7          | I
*------------------------------------------
*Speed (0-255) | PWM   | D6          | I
*------------------------------------------
*
*Brake: INA and INB set to HIGH
*
*QTR-1RC sensors:
*
*Front view of the Sensors location
*
*        B
*       ***
*      *   * A
*       ***
* CW(+)<---> CCW (-)
* 
*Encoder A -> D2 Arduino, external interrupt
*Encoder B -> D3 Arduino, external interrupt
*
*Activation sequence
*                 ______        ______
*  Encoder A  ___|      |______|      |______
*                    ______        ______
*  Encoder B  ______|      |______|      |______
*             CCW-->(-)                   (+) <--CW
*
*Created by Javier Casado July 2016
*/
#include <Encoder.h>
#include <PID_v1.h>
#include <DCMotorServo.h>
#include <MotorDriver.h>
#include <VNH5019MotorDriver.h>
 
#define DATA_BEGIN      '@'
#define pin_dcmoto_dirA 5
#define pin_dcmoto_dirB 7
#define pin_dcmoto_pwm  6
#define pin_current_sensing  A0
#define pin_dcmoto_encodeA 2
#define pin_dcmoto_encodeB 3

VNH5019MotorDriver driver = VNH5019MotorDriver(pin_dcmoto_dirA,pin_dcmoto_dirB,pin_dcmoto_pwm,pin_current_sensing);

Encoder myEncoder = Encoder(pin_dcmoto_encodeB,pin_dcmoto_encodeA);

DCMotorServo servo = DCMotorServo(&driver, &myEncoder);

int targetPosition = 0;

void setup() {

  //Tune the servo feedback
  //Determined by trial and error
  //servo.myPID->SetTunings(0.1,0.15,0.05);
  servo.myPID->SetTunings(0.75,0.0,0.0);
  servo.myPID->SetSampleTime(50);  
  servo.setPWMSkip(30);
  servo.setAccuracy(1);
  //Un-necessary, initializes to 0:
  //servo.setCurrentPosition(0);
  
  Serial.begin(1200);
}


void loop() {
  
  if(readTargetPosition()) servo.moveTo(targetPosition);
  servo.run();
}

/*
 * Returns true when a new position has been read from
 * the Serial port and false otherwise.
 * The value read is stored in the global variable targetPosition.
 */
bool readTargetPosition()
{
	// read speed to be set
	while(Serial.available() > 0) {
		
		// If valid data are comming...
		if(Serial.read() == DATA_BEGIN) {
			
			//wait for the incomming data to arrive, avoids partial readings
			delay(10);
	
	    	targetPosition = Serial.parseInt();
			return true;
		}
		
		// Other info is rubbish, empty the buffer
		while(Serial.available() > 0) Serial.read();
	}
	
   // By default, no reading
   return false;
}
