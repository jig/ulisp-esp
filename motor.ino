#include "motor.h"
#include "pinAssignement.h"

Motor::Motor(int pinPWM, int pinEnable0, int pinEnable1)
{
  reset(pinPWM, pinEnable0, pinEnable1);
}

int Motor::GetSpeedControl()
{
  return SpeedControl;
}

void Motor::SetSpeedControl(int speedControl)
{
  SpeedControl = speedControl;
}

void Motor::Reset()
{
  reset(PinPWM, PinEnable0, PinEnable1);
}

void Motor::reset(int pinPWM, int pinEnable0, int pinEnable1)
{
  PinPWM = pinPWM;

  PinEnable0 = pinEnable0;
  PinEnable1 = pinEnable1;
  digitalWrite(PinEnable0, LOW);
  digitalWrite(PinEnable1, LOW);
  SpeedControl = 0;
  SpeedCounter = 0;
  // Distance = 0;
  SpeedError = 0;
  SpeedIntegralError = 0;
  SpeedDoubleIntegralError = 0;
  LastInput = digitalRead(PinEncoder);
}

void Motor::PIDControl()
{
  int currentSpeedCounter = SpeedCounter;
  int speedLastError = SpeedError;
  SpeedError = currentSpeedCounter - SpeedControl;
  SpeedCounter = 0;

  SpeedIntegralError += SpeedError;
  SpeedDoubleIntegralError += SpeedIntegralError;

  if (SpeedDoubleIntegralError < -1000) {
    SpeedDoubleIntegralError = -1000;
  } else if (SpeedDoubleIntegralError > 1000) {
    SpeedDoubleIntegralError = 1000;
  }

  if (SpeedIntegralError > 50) {
    SpeedIntegralError = 50;
  } else if (SpeedIntegralError < -50) {
    SpeedIntegralError = -50;
  }

  Power = ((-SpeedError * 256) - (SpeedIntegralError * 16) - SpeedDoubleIntegralError) / 16;
  if (Power > 255) {
    Power = 255;
  } else if (Power < -255) {
    Power = -255;
  }
  if (Power > 0) {
    digitalWrite(PinEnable0, LOW);
    digitalWrite(PinEnable1, HIGH);
    analogWrite(PinPWM, Power);
  } else if (Power < 0) {
    digitalWrite(PinEnable0, HIGH);
    digitalWrite(PinEnable1, LOW);
    analogWrite(PinPWM, -Power);
  } else {
    digitalWrite(PinEnable0, LOW);
    digitalWrite(PinEnable1, LOW);
    analogWrite(PinPWM, 0);
  }
}

Motor MotorFrontLeft(MOTOR_PWM_FRONT_LEFT,  MOTOR_FL_0, MOTOR_FL_1);
Motor MotorFrontRight(MOTOR_PWM_FRONT_RIGHT, MOTOR_FR_0, MOTOR_FR_1);
Motor MotorRearLeft(MOTOR_PWM_REAR_LEFT, MOTOR_RL_0, MOTOR_RL_1);
Motor MotorRearRight(MOTOR_PWM_REAR_RIGHT, MOTOR_RR_0, MOTOR_RR_1);

void ISR_MotorFrontLeftA()
{
  int A = digitalRead(ENCODER_FRONT_LEFT_A);
  int B = digitalRead(ENCODER_FRONT_LEFT_B);
  if (A == B) {
    ++MotorFrontLeft.SpeedCounter;
    ++MotorFrontLeft.Distance;
  } else {
    --MotorFrontLeft.SpeedCounter;
    --MotorFrontLeft.Distance;
  }
}

void ISR_MotorFrontLeftB()
{
  int A = digitalRead(ENCODER_FRONT_LEFT_A);
  int B = digitalRead(ENCODER_FRONT_LEFT_B);
  if (A != B) {
    ++MotorFrontLeft.SpeedCounter;
    ++MotorFrontLeft.Distance;
  } else {
    --MotorFrontLeft.SpeedCounter;
    --MotorFrontLeft.Distance;
  }
}

void ISR_MotorFrontRightA()
{
  int A = digitalRead(ENCODER_FRONT_RIGHT_A);
  int B = digitalRead(ENCODER_FRONT_RIGHT_B);
  if (A != B) {
    ++MotorFrontRight.SpeedCounter;
    ++MotorFrontRight.Distance;
  } else {
    --MotorFrontRight.SpeedCounter;
    --MotorFrontRight.Distance;
  }
}

void ISR_MotorFrontRightB()
{
  int A = digitalRead(ENCODER_FRONT_RIGHT_A);
  int B = digitalRead(ENCODER_FRONT_RIGHT_B);
  if (A == B) {
    ++MotorFrontRight.SpeedCounter;
    ++MotorFrontRight.Distance;
  } else {
    --MotorFrontRight.SpeedCounter;
    --MotorFrontRight.Distance;
  }
}

void ISR_MotorRearLeftA()
{
  int A = digitalRead(ENCODER_REAR_LEFT_A);
  int B = digitalRead(ENCODER_REAR_LEFT_B);
  if (A == B) {
    ++MotorRearLeft.SpeedCounter;
    ++MotorRearLeft.Distance;
  } else {
    --MotorRearLeft.SpeedCounter;
    --MotorRearLeft.Distance;
  }
}

void ISR_MotorRearLeftB()
{
  int A = digitalRead(ENCODER_REAR_LEFT_A);
  int B = digitalRead(ENCODER_REAR_LEFT_B);
  if (A != B) {
    ++MotorRearLeft.SpeedCounter;
    ++MotorRearLeft.Distance;
  } else {
    --MotorRearLeft.SpeedCounter;
    --MotorRearLeft.Distance;
  }
}

void ISR_MotorRearRightA()
{
  int A = digitalRead(ENCODER_REAR_RIGHT_A);
  int B = digitalRead(ENCODER_REAR_RIGHT_B);
  if (A != B) {
    ++MotorRearRight.SpeedCounter;
    ++MotorRearRight.Distance;
  } else {
    --MotorRearRight.SpeedCounter;
    --MotorRearRight.Distance;    
  }
}

void ISR_MotorRearRightB()
{
  int A = digitalRead(ENCODER_REAR_RIGHT_A);
  int B = digitalRead(ENCODER_REAR_RIGHT_B);
  if (A == B) {
    ++MotorRearRight.SpeedCounter;
    ++MotorRearRight.Distance;
  } else {
    --MotorRearRight.SpeedCounter;
    --MotorRearRight.Distance;    
  }
}
