
/* Code for PICT Robotics FE Workshop 2024
 *
 * Date: 7 Nov 2024
 *
 * This code incorporates the networking, motor driving, sensor code
 * for the Holonomic Bot build.
 *
 * Contributors: Hrushikesh, Kaushal, Nimish, Tanaya
 *
 */

/* Required for Dabble */
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <DabbleESP32.h>
#include <Arduino.h>

/* custom headers (also .ino files motor.ino, network.ino) */
#include "definitions.h"				/* constants */
#include "motor.h"							/* motor functions */

/* "Out" state */
volatile bool isOut = false;

void setup() {
	Serial.begin(115200);

	/* Initialize motor direction pins */
	setup_motors();

	/* Initialize Hall sensor and LED pins */
	pinMode(HALL_SENSOR_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);

	/* initialize dabble and set Bluetooth Name */
	Dabble.begin("Holonomic Hunter"); 

  
  // setMotor(M0_IN1, M0_IN2, M0_PWM, 255);
  // setMotor(M1_IN1, M1_IN2, M1_PWM, 255);
  // setMotor(M2_IN1, M2_IN2, M2_PWM, 255);
  // setMotor(M3_IN1, M3_IN2, M3_PWM, 255);
}

void loop() {
	if (digitalRead(HALL_SENSOR_PIN))
	{
		//isOut = true;								/* bot is out */
		digitalWrite(LED_PIN, HIGH); /* led should glow */
	}

	/* This function handles the communication between phone and
	 * esp32 */
	Dabble.processInput();

  //move_in_direction_serial(255,0);

  // analogWrite(M0_PWM, 255);
  // analogWrite(M1_PWM, 255);
  // analogWrite(M2_PWM, 255);
  // analogWrite(M3_PWM, 255);


	/* Only move the bot if it is not out */
	if (!isOut)
	{
		/* dabble controls have max value of 7, we need to convert it to
		 * max of 255. So we apply this scaling factor */
		
		float scaling  = 255.0 / 7.0; 
		int velx = scaling * GamePad.getXaxisData();
		int vely = scaling * GamePad.getYaxisData();

    Serial.print("velx: ");
    Serial.print(velx);
    Serial.print(", vely: ");
    Serial.println(vely);
		
		move_in_direction_serial(velx, vely);
	}


	/* this condition is only for debugging purpose 
	 * TODO: remove in final version */
	if (GamePad.isStartPressed())
	{
		isOut = false;							/* bot is again in the game */
		digitalWrite(LED_PIN, LOW);	/* turn led off */
	}
	
}
