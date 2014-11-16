#pragma config(Sensor, S1, Color, sensorI2CHiTechnicColor)
#pragma config(Sensor, S2, Touch, sensorTouch)
#pragma config(Sensor, S3, HTIRL, sensorI2CCustom)
#pragma config(Motor, motorA, A, tmotorNXT, PIDControl, encoder)
#pragma config(Motor, motorB, B, tmotorNXT, PIDControl, encoder)
#pragma config(Motor, motorC, C, tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard !!*//

// Git test

#include "HS485Connect.h"
#include "hitechnic-irlink.h"

byte irport = 1;
int SVT;

float beta = 0, b = 0, db = 2;

task loadingReg()
{
    nMotorEncoder[A] = 0;
    while (true) {
        b += sgn(beta - b) * db;
        float e = (b - nMotorEncoder[C]) * 2;
        motor[C] += e;
    }
}

task touchSensor()
{
    while (SVT == 0)
        wait1Msec(1);
    motor[A] = motor[B] = 0;
    while (nMotorEncoder[C] < 90)
        wait1Msec(1);
    motor[C] = -60;
    while (nMotorEncoder[C] > 5)
        wait1Msec(1);
    motor[C] = 0;
}

float alpha = 0, k = 0.5;

task knockOff()
{
    while (true) {
        SVT = SensorValue[Touch];
        motor[A] = k * (alpha - nMotorEncoder[A]);
        wait1Msec(1);
    }
}

void waitStart()
{
    wait1Msec(1000);
    while (iRezult != 139) {
        nxtDisplayBigTextLine(0, "%d", iRezult);
        wait1Msec(15);
    }
    for (int i = 0; i < 100; ++i) {
        Transmit(138);
        wait1Msec(15);
    }
}

void startMotor(int speed)
{
    PFMotor(pfmotor_S3_C1_A, (ePWMMotorCommand)speed);
    PFMotor(pfmotor_S3_C1_B, (ePWMMotorCommand)speed);
    wait1Msec(10);
}

void stopMotors()
{
    PFcomboDirectMode(HTIRL, irport - 1, CDM_MOTOR_BRAKE, CDM_MOTOR_BRAKE);
    wait1Msec(10);
}

task buttons() // Stop control
{
    while (true) {
        if (nNxtButtonPressed == 0) {
            stopMotors();

            StopAllTasks();
        }
        wait1Msec(10);
    }
}

task main()
{
    nNxtExitClicks = 2;
    StartTask(buttons);
    setupHighSpeedLink();
    //waitStart();
    SensorValue[Color] = 0;
    StartTask(touchSensor);
    nMotorEncoder[A] = 0;
    StartTask(knockOff);
    int cnt = 0;
    while (cnt < 4) {
        motor[B] = -50;
        int color = SensorValue[Color];
        if (7 <= color && color <= 10) {
            motor[B] = 0;
            alpha -= 360;
            motor[B] = 0;
            ++cnt;
            wait1Msec(500);
        }
        wait1Msec(1);
        nxtDisplayBigTextLine(3, "%d", SensorValue[Color]);
    }
    PlaySound(soundBeepBeep);
    wait1Msec(2000);
    while (SVT == 0)
        startMotor(7);
    time1[0] = 0;
    while (time1[0] < 1000)
        stopMotors();
    time1[0] = 0;
    while (time1[0] < 10000)
        startMotor(7);
    time1[0] = 0;
    while (239)
        stopMotors();
}
