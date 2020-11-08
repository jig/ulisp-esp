#ifndef _PIN_H
#define _PIN_H

// Encoders (B encoders only in Ardunio DUE, since all pins can be used as external Interrupts)
#  define ENCODER_FRONT_LEFT_A    26
#  define ENCODER_FRONT_LEFT_B    27
#  define ENCODER_FRONT_RIGHT_A   34
#  define ENCODER_FRONT_RIGHT_B   35
#  define ENCODER_REAR_LEFT_A     42
#  define ENCODER_REAR_LEFT_B     43
#  define ENCODER_REAR_RIGHT_A    50
#  define ENCODER_REAR_RIGHT_B    51
  
#  define MOTOR_PWM_FRONT_LEFT    3
#  define MOTOR_PWM_FRONT_RIGHT   2
#  define MOTOR_PWM_REAR_LEFT     5
#  define MOTOR_PWM_REAR_RIGHT    4
  
#  define SERVO_PWM_CAMERA        6
#  define SERVO_PWM_2             7
#  define SERVO_PWM_3             8
    
#  define MOTOR_FL_0              33
#  define MOTOR_FL_1              37
#  define MOTOR_FR_0              39
#  define MOTOR_FR_1              41
#  define MOTOR_RL_0              31
#  define MOTOR_RL_1              29 
#  define MOTOR_RR_0              45
#  define MOTOR_RR_1              47
  
#  define BATTERY_FRONTWHEELS_PIN A0
#  define BATTERY_REARWHEELS_PIN  A1
#  define BATTERY_SYSTEM_PIN      A2
#endif
