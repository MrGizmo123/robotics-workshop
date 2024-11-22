/* Code for PICT Robotics FE Workshop 2024
 *
 * Date: 7 Nov 2024
 *
 * This code incorporates the networking, motor driving, sensor code
 * for the Holonomic Bot build.
 *
 * Contributors: Hrushikesh, Kaushal, Nimish, Toshit
 *
 */

/* Required for Dabble */
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <DabbleESP32.h>
#include <Arduino.h>

/* custom headers (also .ino files motor.ino, network.ino) */
#include "definitions.h"        /* constants */
#include "motor.h"              /* motor functions */

/* "Out" state */
volatile bool isOut = false;

void setup() {
  /* Serial begin */

  /* Initialize motor direction pins */

  /* Initialize Hall sensor pins */
  
  /* initialize dabble and set Bluetooth Name */
}

void loop() {
  
  /* Add check for Hall Sensor Input */

  /* Only move the bot if it is not out */

  /* reset the bot */
  
}
