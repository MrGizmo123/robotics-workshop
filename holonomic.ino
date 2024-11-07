
/* Code for PICT Robotics FE Workshop 2024
 *
 * Date: 7 Nov 2024
 *
 * This code incorporates the networking, motor driving, sensor code
 * for the Holonomic Bot build.
 *
 * Contributors: Hrushikesh, Kaushal, Tanaya
 *
 */

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>

/* custom headers (also .ino files motor.ino, network.ino) */
#include "definitions.h"				/* constants */
#include "motor.h"							/* motor functions */
#include "network.h"						/* networking functions */

/* "Out" state */
volatile bool isOut = false;
AsyncUDP udp;

/* needs IRAM_ATTR for proper functioning */
IRAM_ATTR void udp_callback(AsyncUDPPacket &packet) {
	if (!isOut)
	{
		
	}
}

void setup() {
	Serial.begin(115200);

	/* Initialize motor direction pins */
	setup_motors();

	/* Initialize Hall sensor and LED pins */
	pinMode(HALL_SENSOR_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);

	
	/* connect to wifi and setup callback */
	if (connect_wifi(udp, SSID, PASS))
	{
		if (start_server(udp, PORT))
		{
			udp_on_packet(udp, udp_callback, true);
		}
	}

}

void loop() {
	if (digitalRead(HALL_SENSOR_PIN))
	{
		isOut = true;								/* bot is out */
		digitalWrite(LED_PIN, HIGH); /* led should glow */
	}
}


