/* Motor driver all direction pins for L293D front left right , back  left right. */
#define M0_IN1 15 		/* top left */
#define M0_IN2 2

#define M1_IN1 17		/* top right */
#define M1_IN2 16

#define M2_IN1 5		/* bottom right */
#define M2_IN2 18

#define M3_IN1 21		/* bottom left */
#define M3_IN2 22

#define DIR_SER 15
#define DIR_CLK 17
#define DIR_LATCH 5

/* Motor driver PWM pins */
#define M0_PWM 0		/* top left */
#define M1_PWM 4		/* top right */
#define M2_PWM 19		/* bottom right */
#define M3_PWM 23		/* bottom left */

/* Hall sensor + status LED */
#define HALL_SENSOR_PIN 1
#define LED_PIN 12

/* constants to make sure each wheel spins at same speed */
#define k0 1
#define k1 1
#define k2 1
#define k3 1

/* Hotspot credentials */
#define SSID "Phone_1_7018"
#define PASS "p0155on3d"
