/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */
//#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <libplayerc++/playerc++.h>

using namespace PlayerCc;
void  printInfo(int angle, Position2dProxy* pp, double distance);

int main() {

	PlayerClient pc("localhost", 6665);
	Position2dProxy pp(&pc);
	SonarProxy sp(&pc,0);
	double forwardSpeed, turnSpeed;
	int angle;
	bool obstacle;
	pp.SetMotorEnable(true);
	while (true)
	{
		pc.Read();

		 if(sp.GetScan(2) < 0.8 )
		 {

			 forwardSpeed = 0.1;
		     if (sp.GetScan(0) < sp.GetScan(4))
		     {
		    	 forwardSpeed = 0;
		    	 turnSpeed = -90;
		     }
		     else
		     {
		    	 forwardSpeed = 0;
				 turnSpeed = 90;
		     }

		 }
		 else
		 {
			 turnSpeed = 0;
			 forwardSpeed = 0.5;
		 }


		 printInfo(90, &pp, sp.GetScan(0));
		 printInfo(25, &pp, sp.GetScan(1));
		 printInfo(0, &pp, sp.GetScan(2));
		 printInfo(-25, &pp, sp.GetScan(3));
		 printInfo(-90, &pp, sp.GetScan(4));

		pp.SetSpeed(forwardSpeed,  dtor(turnSpeed));


	}
	return 0;

}

 void printInfo(int angle,Position2dProxy* pp, double distance)
{
	 if (distance < 0.8)
	 {
		 std::cout << "distance: "<< distance << std::endl;
		 std::cout << "x: " << (*pp).GetXPos() << std::endl;
		 std::cout << "Y: " << (*pp).GetYPos() << std::endl;
		 std::cout << "Yaw: " << (*pp).GetYaw() << std::endl;
		 std::cout << "sensor location: " << angle << std::endl;
	 }
}
