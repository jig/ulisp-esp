#ifndef _MOTOR_H_
#define _MOTOR_H_

class Motor
{
private:
    int PinPWM;
    int PinEncoder;
    int PinEnable0;
    int PinEnable1;
    int SpeedControl;
    void reset(int pinPWM, int pinEnable0, int pinEnable1);
public:
    int SpeedCounter;
    long Distance;
    int SpeedError;
    int SpeedIntegralError;
    int SpeedDoubleIntegralError;
    int LastInput;
    int Power;

    Motor(int pinPWM, int pinEnable0, int pinEnable1);
    void SetSpeedControl(int speedControl);
    int GetSpeedControl();
    void Reset();
    
    void PIDControl();
};

extern Motor MotorFront;
extern Motor MotorRear;

void ISR_MotorFront();
void ISR_MotorRear();

#endif
