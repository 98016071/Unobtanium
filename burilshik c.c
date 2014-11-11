
int usta = 0;
task regul
{
	while(true)
	{
		int e = usta - nMotorEncoder[motorA];
		int u = e*(e < 0 ? 2 : 0.5);
		motor[motorA] = u;
		wait1Msec(5);
	}
}

task main()
{
	nMotorEncoder[motorA] = 0;
	wait1Msec(100);

	StartTask(regul);

	for(int i = 0; i < 5; i++)
	{
		wait1Msec(2000);
		usta = -70;
		wait1Msec(800);
		motor[motorB] = 100;
		wait1Msec(2000);
		motor[motorB] = 0;
		usta = 0;
	}
	wait1Msec(2000);
	usta = -70;
	wait1Msec(800);
	motor[motorB] = 100;
	motor[motorC] = 100;
	wait1Msec(4000);
	usta = 0;
	motor[motorB] = 0;
	motor[motorC] = 0;
	wait1Msec(2000);
	sendMessage(239);
}
