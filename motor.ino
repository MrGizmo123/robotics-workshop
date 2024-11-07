
void setup_motors()
{
	pinMode(M1_IN1, OUTPUT);
	pinMode(M1_IN2, OUTPUT);
	pinMode(M2_IN1, OUTPUT);
	pinMode(M2_IN2, OUTPUT);
	pinMode(M3_IN1, OUTPUT);
	pinMode(M3_IN2, OUTPUT);
	pinMode(M4_IN1, OUTPUT);
	pinMode(M4_IN2, OUTPUT);

	pinMode(M1_PWM, OUTPUT);
	pinMode(M2_PWM, OUTPUT);
	pinMode(M3_PWM, OUTPUT);
	pinMode(M4_PWM, OUTPUT);
}

/* moves the bot in a given direction, x and y components of velocity must be given */
void move_in_direction(int x, int y) {
	
  int val1 = ((float)(x + y))/1.414; /* activation of wheels 2 and 4 */
  int val2 = ((float)(y - x))/1.414; /* activation of wheels 1 and 3 */

  setMotor(M1_IN1, M1_IN2, M1_PWM, val2 * k1);
  setMotor(M2_IN1, M2_IN2, M2_PWM, val1 * k2);
  setMotor(M3_IN1, M3_IN2, M3_PWM, val2 * k3);
  setMotor(M4_IN1, M4_IN2, M4_PWM, val1 * k4);
}

// to set motor direction and speed using PWM
void setMotor(int in1, int in2, int pwmChannel, int speed) {
  speed = constrain(speed, -255, 255);
  int pwmSpeed = abs(speed);

  if (speed > 0) {							/* one direction */
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
	else if (speed < 0) {					/* other direction */
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } 
	else {												/* stop */
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW); 
  }

  /* set pwm speed */
  analogWrite(pwmChannel, pwmSpeed);
}

/* stop the bot */
void stopMotors() {
  setMotor(M1_IN1, M1_IN2, M1_PWM, 0);
  setMotor(M2_IN1, M2_IN2, M2_PWM, 0);
  setMotor(M3_IN1, M3_IN2, M3_PWM, 0);
  setMotor(M4_IN1, M4_IN2, M4_PWM, 0);
}
