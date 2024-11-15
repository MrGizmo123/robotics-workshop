
bool m_dirns[4];

void setup_motors()
{
//	pinMode(M0_IN1, OUTPUT);
//  pinMode(M0_IN2, OUTPUT);
//  pinMode(M1_IN1, OUTPUT);
//  pinMode(M1_IN2, OUTPUT);
//  pinMode(M2_IN1, OUTPUT);
//  pinMode(M2_IN2, OUTPUT);
//  pinMode(M3_IN1, OUTPUT);
//  pinMode(M3_IN2, OUTPUT);

  pinMode(DIR_SER, OUTPUT);
  pinMode(DIR_CLK,OUTPUT);
  pinMode(DIR_LATCH, OUTPUT);

 
	pinMode(M0_PWM, OUTPUT);
	pinMode(M1_PWM, OUTPUT);
	pinMode(M2_PWM, OUTPUT);
	pinMode(M3_PWM, OUTPUT);
}

/* moves the bot in a given direction, x and y components of velocity must be given */
void move_in_direction(int x, int y) {
	
  int val1 = ((float)(x + y))/1.414; /* activation of wheels 2 and 4 */
  int val2 = ((float)(y - x))/1.414; /* activation of wheels 1 and 3 */

  setMotor(M0_IN1, M0_IN2, M0_PWM, val2 * k0);
  setMotor(M1_IN1, M1_IN2, M1_PWM, val1 * k1);
  setMotor(M2_IN1, M2_IN2, M2_PWM, val2 * k2);
  setMotor(M3_IN1, M3_IN2, M3_PWM, val1 * k3);
}

/* moves the bot in a given direction, x and y components of velocity must be given */
void move_in_direction_serial(int x, int y) {
  
  int val1 = ((float)(x + y))/1.414; /* activation of wheels 2 and 4 */
  int val2 = ((float)(y - x))/1.414; /* activation of wheels 1 and 3 */

  setMotor_serial(0, M0_PWM, val2 * k0);
  setMotor_serial(1, M1_PWM, val1 * k1);
  setMotor_serial(2, M2_PWM, val2 * k2);
  setMotor_serial(3, M3_PWM, val1 * k3);
}

void my_shift_out(int data_pin, int clk, int latch, byte data)
{
  digitalWrite(clk, LOW);

  Serial.print("Shift Out: ");

  for (int i = 7;i>=0;i--)
  {
    digitalWrite(data_pin, (data >> i) & 0b1);

    Serial.print((data >> i) & 0b1);

    delayMicroseconds(10);
    digitalWrite(clk, HIGH);
    delayMicroseconds(10);
    digitalWrite(clk, LOW);
    delayMicroseconds(10);
  }

  Serial.println();

  digitalWrite(latch, HIGH);
  delayMicroseconds(10);
  digitalWrite(latch, LOW);

}

void output_directions(bool m_dirn[4])
{
  byte output = !m_dirn[3] << 7 | !m_dirn[2] << 6 |
                m_dirn[3] << 5 | !m_dirn[1] << 4 | 
                !m_dirn[0] << 3 | m_dirn[0] << 2 |
                m_dirn[1] << 1 | m_dirn[2];

  Serial.println(output, BIN);

//  my_shift_out(DIR_SER, DIR_CLK, DIR_LATCH, output);

  digitalWrite(DIR_LATCH, LOW);
  shiftOut(DIR_SER, DIR_CLK, MSBFIRST, output);
  digitalWrite(DIR_LATCH, HIGH);
  delayMicroseconds(1);
  
}

// to set motor direction and speed using PWM
void setMotor_serial(int motor, int pwmChannel, int speed) {
  speed = constrain(speed, -255, 255);
  int pwmSpeed = abs(speed);

  if (speed > 0) {              /* one direction */
    m_dirns[motor] = true;
  }
  else if (speed < 0) {         /* other direction */
    m_dirns[motor] = false;
  }

  output_directions(m_dirns);

  /* set pwm speed */
  analogWrite(pwmChannel, pwmSpeed);
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
  else        /* off */
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }

  /* set pwm speed */
  analogWrite(pwmChannel, pwmSpeed);
}

/* stop the bot */
void stopMotors() {
  setMotor(M0_IN1, M0_IN2, M0_PWM, 0);
  setMotor(M1_IN1, M1_IN2, M1_PWM, 0);
  setMotor(M2_IN1, M2_IN2, M2_PWM, 0);
  setMotor(M3_IN1, M3_IN2, M3_PWM, 0);
}
