#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    AutonSelect,    sensorPotentiometer)
#pragma config(Sensor, in8,    RightArmAngle,  sensorPotentiometer)
#pragma config(Sensor, dgtl1,  waitingButtonRed, sensorTouch)
#pragma config(Sensor, dgtl11, LaunchSolenoid, sensorDigitalOut)
#pragma config(Sensor, dgtl12, waitingButtonBlue, sensorTouch)
#pragma config(Sensor, I2C_1,  LeftIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  RightIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           LeftArm,       tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           RightFWheel,   tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port3,           RightMWheel,   tmotorVex393HighSpeed, openLoop, reversed, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port4,           RightBWheel,   tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port5,           LeftIntake,    tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port6,           RightIntake,   tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port7,           LeftBWheel,    tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port8,           LeftMWheel,    tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port9,           LeftFWheel,    tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port10,          RightArm,      tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

/******************************************
///////// FINAL VARIABLES HERE ///////////
///////// PLACE NECESSARY USER ///////////
//////////CONTROL AND AUTON //////////////
///////// FUNCTIONS HERE /////////////////
******************************************/

////////////////////////////
//***** Drive Values *****//
////////////////////////////
	int FORWARD = 0;
	int BACKWARD = 1;
	int LEFT = 2;
	int RIGHT = 3;

	int TILE = 500; // Theoretically accurate
	int HALF_TILE = 250; // 12"
	int TICK_THEORY = 2865; // ticks per hundred inches
	int TICK_AVG = 2850; // ticks per hundred inches
	int PRE_GOAL = 1600;
	int GOAL = 1900;
	int RIGHT_ANGLE = 200; // must test

	int HUNDRED = 127;
	int FIFTY = 64;
	int THIRTY_SEVEN = 48;
	int TWENTY_FIVE = 32;

	int control = 10;		// tested zero, too much control is bad.
////////////////////
//** Arm Values **//
////////////////////
	int BARRIER = 1000;	// Potentiometer value for arm to go over 12" barrier
	int LOW = 150;				// Potentiometer value for arm to reach minimum...Actual value is 550-590...Safety 600 is too high
	int BUMP = 300;		// Lag between pinion and 60 tooth gear -> ranges 600-800...Safety 750
	int HIGH = 1350;		// Ranges between 1750-1900, left is 1750 and right is 1880...Safety 1750
	//int PRE_HIGH = 4000;// Just before stretched maximum reach
	int SAFETY_HIGH = 1380; // don't go higher than this please

	int hold = 15; // Arbitrary Numbers tested: 45 too high, 30 holds, 25 holds...testing 15

//////////////////////////
//**** AUTON SELECT ****//
//////////////////////////
	int ALEX = 700;
	int UDIT = 2200;
	int DEVANSH = 3800;

/******************************************
///////// VOID FUNCTIONS HERE ////////////
///////// PLACE NECESSARY USER ///////////
//////////CONTROL AND AUTON //////////////
///////// FUNCTIONS HERE /////////////////
******************************************/
	void pre_auton()
	{
		bStopTasksBetweenModes = true; // This is necessary
	}

// Drive Functions here
	int cubicScaling(int x)
	{
	 	return ((((x*3)/25)*((x*3)/25)*((x*3)/25)/27 + x/2)*2)/3; //dead zone of +-3...
	}

	int hardCubicScaling(int x)
	{
		return ((x*x*x) / (127*127)); //dead zone of +- 25...
	}

// Auton Functions here
	void setLeft(int pwr)
	{
		motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = pwr;
	}

	void setRight(int pwr)
	{
		motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = pwr;
	}

	void resetValues(int wait) //reset values to zero for safety - Encoders, Timers and Motors
	{
			wait1Msec(wait);
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = 0;
			motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = 0; // drive motors set to zero
			motor[LeftArm] = motor[RightArm] = 0; // arm motors set to zero
			motor[LeftIntake] = motor[RightIntake] = 0; // intake motors set to zero
			nMotorEncoder[LeftMWheel] = 0; //IEMs set to zero
	}

	void preciseDriveStop(int Case) // For now... Select each case to precision stop, idk how to get motor power
	{
		if(Case == FORWARD) // FORWARD if moving forwards -> negative input sharp stop
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = -10;
		else if(Case == BACKWARD) // BACKWARD etc...
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = 10;
		else if(Case == LEFT) // LEFT
		{
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = 5;
			motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = -5;
		}
		else if(Case == RIGHT) // RIGHT
		{
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = -5;
			motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = 5;
		}
		else
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = 0;
		wait1Msec(1000); // stabilization time
	}

	void noRamp(int direction, int distance)
	{
		nMotorEncoder[LeftMWheel] = 0;
		while(abs(nMotorEncoder[LeftMWheel]) < distance)
		{
			setLeft(direction*FIFTY); setRight(direction*FIFTY);
		}
		if(direction>0)
		{
			preciseDriveStop(FORWARD);
		}
		else
		{
			preciseDriveStop(BACKWARD);
		}
	}

	void noRampFast(int direction, int distance)
	{
		nMotorEncoder[LeftMWheel] = 0;
		while(abs(nMotorEncoder[LeftMWheel]) < distance)
		{
			setLeft(direction*100); setRight(direction*100);
		}
		if(direction>0)
		{
			preciseDriveStop(FORWARD);
		}
		else
		{
			preciseDriveStop(BACKWARD);
		}
	}

	void noRampSlow(int direction, int distance)
	{
		nMotorEncoder[LeftMWheel] = 0;
		while(abs(nMotorEncoder[LeftMWheel]) < distance)
		{
			setLeft(direction*30); setRight(direction*30);
		}
		if(direction>0)
		{
			preciseDriveStop(FORWARD);
		}
		else
		{
			preciseDriveStop(BACKWARD);
		}
	}

	// time is in milliseconds
	// distance is in tenths of inches
	// direction is 1 or -1 -- positive is forwards
	void moveStraight(int direction, int time, int driveTarget)
	{
		nMotorEncoder[LeftMWheel] = 0;
		int distance = 0;
		float pwr = 0;
			while(distance < driveTarget )
			{

					distance = abs(nMotorEncoder[LeftMWheel]);
					//initial version
					//pwr = 64 * sin(distance * PI / driveTarget);
					//improved version

					//SHITTY PID:
					//pwr = 0.05 * (driveTarget - distance) + 0.0003 * (0.05 * (driveTarget * distance - 0.5 * (distance * distance)));

					if( distance <= driveTarget / 2)
				  pwr = distance / 5 + 25; //TODO: figure out how this works
						// please don't touch precalibrated code.
					else
						pwr = ( driveTarget - distance ) / 10 + 25;

						//pwr = -1 * (1.11 * sqrt(driveTarget) - 10) * cos(distance * 2 * PI / driveTarget) + (1.11 * sqrt(distance)) + 10;
					pwr *= direction;
					setLeft(pwr);
					setRight(pwr);
			}
			setLeft(0);
			setRight(0);
		}

	void PIDStraight(int direction, int time, int driveTarget)
	{

	}

	// direction is binary -1 or 1, positive is right
	// time is milliseconds
	// degrees is always positive
	void spin(int direction, int time, int degrees) // we need to calculate degrees per tick
	{
		nMotorEncoder[LeftMWheel] = 0;
		// Must test - works

		while(abs(nMotorEncoder[LeftMWheel]) < degrees)
		{
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = direction * FIFTY;
			motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = -direction * FIFTY;
		}

		if(direction > 0)
			preciseDriveStop(RIGHT);
		else
			preciseDriveStop(LEFT);
	}

	void softSpin(int direction, int time, int degrees)
	{
		nMotorEncoder[LeftMWheel] = 0;
		// Must test

		while(abs(nMotorEncoder[LeftMWheel]) < degrees)
		{
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = direction * TWENTY_FIVE;
			motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = -direction * TWENTY_FIVE;
		}

		if(direction > 0)
			preciseDriveStop(RIGHT);
		else
			preciseDriveStop(LEFT);
	}

	//shortened and changed to int for ease of use. also replaces 'stopIntake()'.
	void intake(int direction){
			motor[LeftIntake] = motor[RightIntake] = direction * 127;
	}

	void intakeSlow(int direction){
			motor[LeftIntake] = motor[RightIntake] = direction * 80;
	}



	void lift(int targetPot)
	{
		while(SensorValue[RightArmAngle] < targetPot)
		{
				motor[LeftArm] = motor[RightArm] = 120;	 //goes up if lower
		}
		motor[LeftArm] = motor[RightArm] = 0;
	}
	void liftTime(int direction, int time)
	{
		motor[LeftArm] = motor[RightArm] = 127;	 //goes up if lower
		wait1Msec(time);
		motor[LeftArm] = motor[RightArm] = 0;
	}

	void liftDown()
	{
		while(SensorValue[RightArmAngle] > LOW)
		{
			motor[LeftArm] = motor[RightArm] = -127;

	  //  motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] =  30;
			//motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = -30;
		}
		motor[LeftArm] = motor[RightArm] = 0;
	}

	void holdArm()
	{
		motor[LeftArm] = motor[RightArm] = hold;
	}

	void holdArmHigh()
	{
		motor[LeftArm] = motor[RightArm] = 80;
	}

	void waitForButton()
	{
		while(SensorValue[waitingButtonRed] == 0 && SensorValue[waitingButtonBlue] == 0){}
	}

	void deploy()
	{
		intake(1);
		wait10Msec(100);

	}

	void pickUpBall(int goals)
	{
		resetValues(0);
		intake(1);
		wait10Msec(30);
		int current = 0;
		while(current < goals * 250)
		{
			setLeft(25); setRight(25);
			current = nMotorEncoder[LeftMWheel];
		}
		intake(0);
		setLeft(0); setRight(0);
	}

	void crossBump()
	{
		setRight(127); setLeft(127);
		waitForButton();
		setRight(0); setLeft(0);
	}

	/* Psuedocode
			 Ramp Forward -> [Cross Barrier] -> Raise Arm HIGH -> Hold Arm HIGH -> Ramp Zero -> [Reach Goal] -> Outtake -> [Finish Outtake]
			 	-> Stop Intake -> Ramp Forward -> Ramp Zero -> [Reach Barrier] -> Lower Arm LOW -> Ramp Backward -> [Reach Square] -> Hard Zero
			 Wait Until Press -> Raise Arm BARRIER -> Hold Arm BARRIER -> Ramp Forward -> Ramp Zero -> [Reach Barrier] -> Ramp Backward
			 	-> [Reach Square] -> Hard Zero -> Wait Until Press -> Ramp Forward -> Ramp Zero -> [Reach Barrier]
	*/

	void BlueSai() //potential 20pt auton
	{
		deploy();

		// go for second ball knockdown
		noRamp(1,1800);


	}


	void RedSai() //potential 20pt auton
	{
		deploy();

		// go for second ball knockdown
		moveStraight(1, 0, 950);
		wait1Msec(300);
		moveStraight(-1, 0, 950);
		resetValues(100);

		waitForButton();
		moveStraight(1,0,1500); //move forward
		spin(-1,0,180); // turn towards the cache
		lift(HIGH); // nearest 100
		holdArmHigh();
		moveStraight(1, 0, 650); // reaches goal
		intake(-1);
		wait1Msec(1000); // outtake




	}

	void Bistromathics()
	{
		deploy();
		intake(1);



		noRampFast(1,2400);

		lift(BARRIER-200);
		holdArm();

		intake(-1);


		spin(1,0,400);
		spin(-1,0,400);



	}

	void AlexAlt() // Caches preload (5) + Knocks 2 big balls (10)
	{
		deploy();
	wait10Msec(100);
		lift(BARRIER);
		holdArm();
		intake(-1);
		moveStraight(1, 0, 580); //estimated guess based on 10Q's values
		wait1Msec(300);
		//moveStraight(-1, 0, 550);
		moveStraight(-1, 0, 580);
		//waitForButton();
		wait10Msec(80);
		moveStraight(1, 0, 950);
		wait1Msec(300);
		moveStraight(-1, 0, 950);



		wait10Msec(80);
		moveStraight(1, 0, 1420); // maintenence and recalibrating needed
		lift(HIGH); // nearest 100
		holdArmHigh();
		moveStraight(1, 0, 500); // reaches goal
		//wait1Msec(1000);
		intake(-1);
		wait1Msec(500); // outtake
		moveStraight(-1, 0, 400); //move back away from goal...Apparently Safety is greater than move forward
		liftDown();
			// end score bucky
		moveStraight(-1, 0, 1300); // now user readjust for first ballb
		//waitForButton();


		resetValues(100);


	}


	void Alex() // Caches preload (5) + Knocks 2 big balls (10)
	{
		//deploy();

		//waitForButton();

		moveStraight(1, 0, 1400); // maintenence and recalibrating needed
		lift(HIGH); // nearest 100
		holdArmHigh();

		moveStraight(1, 0, 430); // reaches goal
		//wait1Msec(1000);
		intake(-1);
		wait1Msec(500); // outtake
		moveStraight(-1, 0, 400); //move back away from goal...Apparently Safety is greater than move forward
		liftDown();
			// end score bucky
		moveStraight(-1, 0, 1300); // now user readjust for first ballb
		//waitForButton();]
		wait10Msec(80);
		lift(BARRIER);
		holdArm();
		intake(-1);
		moveStraight(1, 0, 580); //estimated guess based on 10Q's values
		wait1Msec(300);
		//moveStraight(-1, 0, 550);
		moveStraight(-1, 0, 580);
		//waitForButton();
		wait10Msec(80);
		moveStraight(1, 0, 950);
		wait1Msec(300);
		moveStraight(-1, 0, 950);
		resetValues(100);
	}

	void Alex2() // Knocks 2 big balls (10) then caches preload
	{
		deploy();

		lift(BARRIER);
		holdArm();
		intake(-1);
		moveStraight(1, 0, 580); //estimated guess based on 10Q's values
		wait1Msec(300);
		//moveStraight(-1, 0, 550);
		moveStraight(-1, 0, 580);

		waitForButton();
		moveStraight(1, 0, 950);
		wait1Msec(300);
		//moveStraight(-1, 0, 950);
		moveStraight(-1, 0, 950);
		resetValues(100);

		waitForButton();
		moveStraight(1, 0, 1420); // maintenence and recalibrating needed
		lift(HIGH); // nearest 100
		holdArmHigh();
		moveStraight(1, 0, 500); // reaches goal
		//wait1Msec(1000);
		intake(-1);
		wait1Msec(500); // outtake
		moveStraight(-1, 0, 400); //move back away from goal...Apparently Safety is greater than move forward
		motor[LeftArm] = motor[RightArm] = -127;
		wait1Msec(800);
		motor[LeftArm] = motor[RightArm] = 0;
			// end score bucky
		moveStraight(-1, 0, 1300); // now user readjust for first ball
	}

	void blueDevansh() // Places preload (1-2) + 2 buckies (2-4) + TURN RIGHT Knocks buckies (1-6)
	{
		deploy();
		intake(1);
		wait10Msec(10);
		moveStraight(1, 0, 455); //picks up
		wait10Msec(50);
		moveStraight(-1, 0, 475);//comes back
		intake(0);
				// end part 1: prepare dump
		waitForButton();
		lift(BUMP);
		holdArm();
		intake(-1);
		resetValues(1200);
			// end part 2: dump
		waitForButton();
		liftDown();
		wait10Msec(100);
		moveStraight(1, 0, 700);
			// end part 3: prepare hit
		spin(1, 0, 200);
		intake(-1);
		lift(BUMP);
		holdArm();
		noRamp(1, 250);
		resetValues(0);
			// end part 4: hit
	}

	void redDevansh() // Places preload (1-2) + 2 buckies (2-4) + TURN LEFT Knocks buckies (1-6)
	{
		deploy();
		intake(1);
		wait10Msec(10);
		moveStraight(1, 0, 455); //picks up
		wait10Msec(50);
		moveStraight(-1, 0, 475);//comes back
		intake(0);
				// end part 1: prepare dump
		waitForButton();
		lift(BUMP);
		holdArm();
		intake(-1);
		resetValues(1200);
			// end part 2: dump
		waitForButton();
		liftDown();
		wait10Msec(100);
		moveStraight(1, 0, 700);
			// end part 3: prepare hit
		spin(-1, 0, 200);
		intake(-1);
		lift(BUMP);
		holdArm();
		noRamp(1, 250);
		resetValues(0);
			// end part 4: hit
	}

	void blueUdit()
	{
		deploy();


		wait10Msec(20);
		moveStraight(1, 0, 440); //picks up
		wait10Msec(50);
		moveStraight(-1, 0, 440);//comes back
		intake(1);

		lift(HIGH);



		waitForButton();
		liftDown();

	  wait10Msec(30);

		noRampFast(1,2000);
		spin(1,0, 230);
		//noRampFast(1,40);
		lift(BUMP);
		noRampSlow(-1,70);
	  noRampFast(1,1100);

		intake(-1);
		holdArm();
		wait10Msec(130);
	}

	void redUdit()
	{
		deploy();


		wait10Msec(20);
		moveStraight(1, 0, 440); //picks up
		wait10Msec(50);
		moveStraight(-1, 0, 440);//comes back
		intake(1);

		lift(HIGH);



		waitForButton();
		liftDown();

	  wait10Msec(30);

		noRampFast(1,1400);
		spin(-1,0, 230);
		//noRampFast(1,40);
		lift(BUMP);
	  noRampFast(1,1100);

		intake(-1);
		holdArm();
		wait10Msec(130);

	}
	void blueBrian()
	{
			moveStraight(1, 0, 1000); // estimate going 2 tiles, under bump perpendicular to barrier
			wait10Msec(30); // stableeeeeeeeeeeeeeeee hit ball gently?
			spin(-1, 0, 100); // uh... hopefully it doesn't fall out?
			//wait10Msec(70); 1 sec stabilization time already incorporated in spin()
			lift(HIGH); // uh..
			holdArmHigh();
			wait10Msec(70);
			moveStraight(1, 0, 450);
			wait10Msec(70);
			intake(-1);
			wait10Msec(10); // lol
			intake(0);
			moveStraight(-1, 0, 200); // lol
			intake(-1); // lol
			wait10Msec(20);
			intake(0);
			moveStraight(-1, 0, 250);
			resetValues(0);
			liftDown();
			spin(1, 0, 100);
			moveStraight(-1, 0, 1000);
			waitForButton();
			// end 15 pts

			lift(BARRIER);
			holdArm();
			moveStraight(1, 0, 950);
			// end 5 pts, or 20pts total
	}

	void redBrian()
	{

	}

	void RedBS()
	{
		deploy();


		noRamp(1,500);
		noRampSlow(1,500);
		spin(-1,0, 230);
		//noRampFast(1,40);
		lift(BARRIER - 300);


		moveStraight(1,0,700);//hops bump

		wait10Msec(80);
		lift(BARRIER);
		holdArm();
		moveStraight(1, 0, 580);
		intake(-1);



	}
	void BlueBS()
	{
		deploy();


		noRamp(1,500);
		noRampSlow(1,500);
		spin(1,0, 230);
		//noRampFast(1,40);
		lift(BARRIER - 300);


		moveStraight(1,0,700);//hops bump

		wait10Msec(80);
		lift(BARRIER);
		holdArm();
		moveStraight(1, 0, 580);
		intake(-1);



	}


  void Skills()
  {
  	deploy();

  	/*
  	//moves forward, loading up with 3 buckies
  	wait10Msec(20);
    intakeSlow(1);
		moveStraight(1, 0, 430); //picks up
		wait10Msec(50);
		moveStraight(-1, 0, 400);//comes back
		intake(1);

		//lifts arms and crosses bumb backwards
		lift(BUMP - 50);
		intake(0);
	  holdArm();
		waitForButton();

		moveStraight(-1,0,700);//hops bump


		//one button press to lower lift, another to send it to goal
		waitForButton();
	  liftDown();

  	waitForButton();
		moveStraight(1, 0, 1400); // maintenence and recalibrating needed...1400 worked
		wait10Msec(30);
		lift(HIGH);
		holdArm();//ABSOLUTELY DO NOT USE "holdArmHigh", it is what BROKE THE CODE (i think)
		moveStraight(1, 0, 430); // reaches goal...430 worked
		//wait1Msec(1000);
		intake(-1);
		wait10Msec(150); // outtakes 3
		moveStraight(-1, 0, 400); //move back away from goal
		liftDown();


		moveStraight(-1, 0, 1400);
		waitForButton();
		*/
		intake(-1);
		lift(BARRIER);
		holdArm();
		waitForButton();

		moveStraight(1, 0, 550); // first ball
		wait10Msec(30);
		moveStraight(-1, 0, 500);
		// first ball done

		waitForButton();


		moveStraight(1, 0, 920); // second ball
		wait10Msec(50);
		spin(1, 0, 400);
		wait10Msec(50);
		moveStraight(1, 0, 500);
		wait10Msec(30);
		moveStraight(-1, 0, 500);
		// second ball done

		wait10Msec(30);
		spin(-1, 0, 400);
		wait10Msec(30);



		moveStraight(1, 0, 920); // second ball
		wait10Msec(50);
		softSpin(1, 0, 400);
		wait10Msec(50);
		moveStraight(1, 0, 500);
		wait10Msec(30);
		moveStraight(-1, 0, 500);
		// third ball done

		wait10Msec(30);
		spin(-1, 0, 400);
		wait10Msec(30);

		moveStraight(1, 0, 920); // fourth ball
		wait10Msec(50);
		softSpin(1, 0, 400);
		wait10Msec(50);
		moveStraight(1, 0, 500);
		wait10Msec(30);
		moveStraight(-1, 0, 500);
		// fourth ball

		wait10Msec(30);
		spin(-1, 0, 400);
		wait10Msec(30);

		// 1840
		// 2400
		// 3160
		//

	}

	void autonTest()
	{
		redDevansh();
	}

/*****************************************************
//////// AUTONOMOUS PROGRAM HERE /////////////////////
*****************************************************/

task autonomous()
{
	deploy();
	while(true)
	{
		if(SensorValue[waitingButtonRed] == 1)
		{
			if(SensorValue[AutonSelect] < ALEX)
			{
				Alex(); // 15 middle zone
			}
			else if(SensorValue[AutonSelect] < UDIT)
			{
				redUdit(); // projected 30 pts + spare change (6-14)
			}
			else if(SensorValue[AutonSelect] < DEVANSH)
			{
				Bistromathics();
		 	}
			else{}
			break;
		}
		else if(SensorValue[waitingButtonBlue] == 1)
		{
			if(SensorValue[AutonSelect] < ALEX)
			{
			  Alex();
			}
		  else if(SensorValue[AutonSelect] < UDIT)
			{
				blueUdit();
			}
			else if(SensorValue[AutonSelect] < DEVANSH)
			{
				Bistromathics();
			}
			else{}
			break;
		}
	}
}

// booleans for arm raising
	bool raiseArmBump = false;
	bool raiseArmBarrier = false;
	bool raiseArmHigh = false;
	int armDirection = 0;


task usercontrol()
{
	while(true)
	{
		// Instance Variables
		int RightDrivePower, LeftDrivePower, LiftPower, IntakePower = 0;

		/////////////////////////////
		//*** DEAD ZONE CONTROL ***//
		/////////////////////////////
		int Channel3 = abs(vexRT(Ch3)) < control ? 0 : vexRT(Ch3); // deadzone setting - if abs(y) greater than 25 -> 0, else real value
		int Channel1 = abs(vexRT(Ch1)) < control ? 0 : vexRT(Ch1); // deadzone setting - if abs(x) greater than 25 -> 0, else real value

		///////////////////////////////
		//****** DRIVE CONTROL ******//
		///////////////////////////////

		// Halo Drive
			//Linear Scaling - Joseph has gotten used to this...

			    RightDrivePower = Channel3 - Channel1;
					LeftDrivePower = Channel3 + Channel1;

			//Soft Cubic Scaling - Joseph doesn't like the turning on this, but likes the extra precision
					/*
					RightDrivePower = cubicScaling(vexRT[Ch3]) - cubicScaling(vexRT[Ch1]);
					LeftDrivePower = cubicScaling(vexRT[Ch3]) + cubicScaling(vexRT[Ch1]);
					*/

		// Manual Tank
					/* //Soft Cubic Scaling
					RightDrivePower = cubicScaling(vexRT[Ch2]);
					LeftDrivePower = cubicScaling(vexRT[Ch3]);
					*/

					/* // Hard Cubic Scaling - Not Tested
					RightDrivePower = hardCubicScaling(vexRT[Ch2]);
					LeftDrivePower = hardCubicScaling(vexRT[Ch3]);
					*/

		///////////////////////////
		//***** LIFT CONTROL ****//
		///////////////////////////

		/**************************
		Liimits: Can't go lower than LOW
		Arm Holding: Constant hold between PRE_HIGH and HIGH
		**************************/

		// Logic order -> if no input and already raised -> Constant
		// 		If not -> Check Lowered Safety
		//		If not -> Manual Control
		//PRE-CONDITION: Arm Holding is Autonomous,
		//No user input, but user needs to take manual on demand
		if((vexRT[Btn5U] == 0 && vexRT[Btn5D] == 0) && (SensorValue[RightArmAngle] >= (BUMP)))
			LiftPower = hold;
		else if(SensorValue[RightArmAngle] <= LOW) //LOW Safety Limit
			LiftPower = vexRT[Btn5U]*127 - vexRT[Btn5D]*0; // can only go up now
		/*else if(SensorValue[RightArmAngle] >= SAFETY_HIGH)
		{
			LiftPower = vexRT[Btn5U]*hold - vexRT[Btn5D]*127; // can only go down now
		}*/
		else // Full Manual
			LiftPower = vexRT[Btn5U]*127 - vexRT[Btn5D]*127;

		if(vexRT[Btn8D] == 1) // left bottom button to set to barrier height, may need testing
		{
			while(SensorValue[RightArmAngle] != BARRIER)
			{
				if(SensorValue[RightArmAngle] < BARRIER)
					LiftPower = 127;
				break;
				if(SensorValue[RightArmAngle] > BARRIER)
					LiftPower = -127;
				break;
			}
		}
					/*
		//prototype arm code
		if (vexRT[Btn8U] == 1){
			raiseArmBump = false;
			raiseArmBarrier = false;
			raiseArmHigh = true;
			if (SensorValue[RightArmAngle] <= HIGH){
				armDirection = 1;
			}
			else{
				armDirection = -1;
			}
		}
		else if (vexRT[Btn8R] == 1){
			raiseArmBump = false;
			raiseArmBarrier = true;
			raiseArmHigh = false;
			if (SensorValue[RightArmAngle] <= BARRIER){
				armDirection = 1;
			}
			else{
				armDirection = -1;
			}
		}
		else if (vexRT[Btn8D] == 1){
			raiseArmBump = true;
			raiseArmBarrier = false;
			raiseArmHigh = false;
			if (SensorValue[RightArmAngle] <= BUMP){
				armDirection = 1;
			}
			else{
				armDirection = -1;
			}
		}

		*/



		//////////////////////////
		//*** Intake Control ***//
		//////////////////////////
			IntakePower = vexRT[Btn6U]*127 - vexRT[Btn6D]*127;

		/////////////////////////////
		//*** Pneumatic Control ***//
		/////////////////////////////
			//SensorValue[leftLaunch] = SensorValue[rightLaunch] = vexRT[Btn8U]; // basic holding

			/*
			// Toggle Solenoid Control - Up for 1 and Down for 0

			*/
			/**
			bool toggleSolenoid = false;

			// Logic: Up - 1, Down - 0, Both - 0
			if(vexRT[Btn8U] && !vexRT[Btn8D])
			{
				toggleSolenoid = true;
			}


			SensorValue[leftLaunch] = SensorValue[rightLaunch] = toggleSolenoid;
			*/
			//test counter toggle... above fails
			/*
			int counter = 0;
			// logic: even numbers -> 0, odd -> 1
			SensorValue[leftLaunch] = SensorValue[rightLaunch] = (counter % 2);
*/

		// v 3 FOR LAUNCHING
			bool toggleLaunch;
			if(vexRT[Btn8U] && !vexRT[Btn8D])
			{
				toggleLaunch = true;
			}
			if(vexRT[Btn8D])
			{
				toggleLaunch = false;
			}



	// for hanging
			bool toggleHang;
			if(vexRT[Btn8R] && !vexRT[Btn8L])
			{
				toggleHang = true;
			}

			if(vexRT[Btn8L])
			{
				toggleHang = false;
			}




		/*************************
		****** TESTING AREA ******
		*************************/

				//Set motors to each individual powers...
				motor[RightBWheel] = RightDrivePower; // port 4
				motor[RightMWheel] = RightDrivePower;		// port 3
				motor[RightFWheel] = RightDrivePower;		// port 2
				//setRight(RightDrivePower);
				motor[LeftFWheel] = LeftDrivePower;	// port 9
				motor[LeftMWheel] = LeftDrivePower;	//port 8
				motor[LeftBWheel] = LeftDrivePower;	//port 7
				// ports have changed.... uh... lol idk if above is still correct
				//setLeft(LeftDrivePower);

				motor[RightArm] = motor[LeftArm] = LiftPower;

				motor[RightIntake] = motor[LeftIntake] = IntakePower;

				//Set solenoids to individual powers;
				SensorValue[LaunchSolenoid] = toggleLaunch;

	} // end while update loop
} // end task usercontrol

task Joseph()
{
}
