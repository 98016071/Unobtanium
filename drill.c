#pragma config(Motor, motorA, A, tmotorNXT, PIDControl, encoder)
#pragma config(Motor, motorB, B, tmotorNXT, PIDControl, encoder)
#pragma config(Motor, motorC, C, tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int usta = 0;
float a = 0, da = 2;
task regul()
{
    while (true) {
        a += sgn(usta - a) * da;
        float e = a - nMotorEncoder[A];
        float u = e * (e < 0 ? 2 : 0.5);
        motor[A] = u;
        wait1Msec(5);
    }
}

task main()
{
    motor[A] = 10;
    wait1Msec(2000);
    nMotorEncoder[A] = 0;
    PlaySound(soundBeepBeep);
    wait1Msec(100);

    StartTask(regul);

    for (int i = 0; i < 5; i++) {
        wait1Msec(2000);
        usta = -80;
        wait1Msec(2000);
        motor[B] = 100;
        wait1Msec(2000);
        motor[B] = 0;
        usta = 0;
    }
    wait1Msec(2000);
    usta = -80;
    wait1Msec(2000);
    motor[B] = 100;
    motor[C] = 100;
    wait1Msec(4000);
    usta = 0;
    motor[B] = 0;
    motor[C] = 0;
    wait1Msec(2000);
    sendMessage(239);
}