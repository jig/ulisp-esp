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

Motor MotorFront(MOTOR_PWM_FRONT,  MOTOR_F_0, MOTOR_F_1);
Motor MotorRear(MOTOR_PWM_REAR, MOTOR_R_0, MOTOR_R_1);

void ISR_MotorFrontA()
{
  int A = digitalRead(ENCODER_FRONT_A);
  int B = digitalRead(ENCODER_FRONT_B);
  if (A == B) {
    ++MotorFront.SpeedCounter;
    ++MotorFront.Distance;
  } else {
    --MotorFront.SpeedCounter;
    --MotorFront.Distance;
  }
}

void ISR_MotorFrontB()
{
  int A = digitalRead(ENCODER_FRONT_A);
  int B = digitalRead(ENCODER_FRONT_B);
  if (A != B) {
    ++MotorFront.SpeedCounter;
    ++MotorFront.Distance;
  } else {
    --MotorFront.SpeedCounter;
    --MotorFront.Distance;
  }
}

void ISR_MotorRearA()
{
  int A = digitalRead(ENCODER_REAR_A);
  int B = digitalRead(ENCODER_REAR_B);
  if (A == B) {
    ++MotorRear.SpeedCounter;
    ++MotorRear.Distance;
  } else {
    --MotorRear.SpeedCounter;
    --MotorRear.Distance;
  }
}

void ISR_MotorRearB()
{
  int A = digitalRead(ENCODER_REAR_A);
  int B = digitalRead(ENCODER_REAR_B);
  if (A != B) {
    ++MotorRear.SpeedCounter;
    ++MotorRear.Distance;
  } else {
    --MotorRear.SpeedCounter;
    --MotorRear.Distance;
  }
}
