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
//void AvoidObstacles(double *forwardSpeed, double *turnSpeed, int *angle, LaserProxy &lp);
void Wander(double *forwardSpeed, double *turnSpeed);
int main() {
	double lastobstacle;

	PlayerClient pc("localhost", 6665);
	LaserProxy lp(&pc);
	Position2dProxy pp(&pc);
	SonarProxy sp(&pc,0);
	double forwardSpeed, turnSpeed;
	pp.SetMotorEnable(true);
	while (true)
	{
		pc.Read();
 /**
		std::cout << "---" << std::endl;
		// looks like its right
		std::cout << "sp 0: " << sp.GetScan(0) << std::endl;
		// right tooth
		std::cout << "sp 1: " << sp.GetScan(1) << std::endl;
		// 2 + 6 is front
		std::cout << "sp 2: " << sp.GetScan(2) << std::endl;

		// left tooth
		std::cout << "sp 3: " << sp.GetScan(3) << std::endl;

		// looks like this the left side
		std::cout << "sp 4: " << sp.GetScan(4) << std::endl;

		// right corner
		std::cout << "sp 5: " << sp.GetScan(5) << std::endl;
		// 2 + 6 is front
		std::cout << "sp 6: " << sp.GetScan(6) << std::endl;

		// left corner
		std::cout << "sp 7: " << sp.GetScan(7) << std::endl;
		std::cout << "" << std::endl;
		**/
		// in order to turn in 90 degree i need too set the speed to 0 and turn around
		// 90 degrees is turn right
		//pp.SetSpeed(0, 90);
		// lets check turn to the other way in 90 degrees
		// -90 degrees is to turn left
		//pp.SetSpeed(0, -90);

		 if( (sp.GetScan(2) < 0.4) && (sp.GetScan(6) < 0.4) )
		 {

			 forwardSpeed = 0;

			 // turn right
			 if (sp.GetScan(7) < sp.GetScan(0))
			 {
				 lastobstacle = sp.GetScan(2);
				 turnSpeed = -90;

				 pp.SetSpeed(forwardSpeed,  dtor(turnSpeed));
				 while (sp.GetScan(7) > lastobstacle)
				 {
						 pc.Read();
						 std::cout << "turn right" <<std::endl;
						 std::cout << "sp.GetScan(7):" << sp.GetScan(7) << ", lastobstacle:" << lastobstacle << std::endl;
						 std::cout << "sp.GetScan(0):" << sp.GetScan(0) <<std::endl;
						 sleep(1);
				 }

				 std::cout << "out right" <<std::endl;
				 std::cout << "sp.GetScan(7):" << sp.GetScan(7) << ", lastobstacle:" << lastobstacle << std::endl;
				 std::cout << "sp.GetScan(0):" << sp.GetScan(0) <<std::endl;
			 }
			 // turn left
			 else
			 {
				 turnSpeed = 90;
				 lastobstacle = sp.GetScan(2);
				 pp.SetSpeed(forwardSpeed,  dtor(turnSpeed));

				 while (sp.GetScan(0) > lastobstacle)
				 {
					 pc.Read();
					 std::cout << "turn left" <<std::endl;
					 std::cout << "sp.GetScan(7):" << sp.GetScan(7) << ", lastobstacle:" << lastobstacle << std::endl;
					 std::cout << "sp.GetScan(0):" << sp.GetScan(0) <<std::endl;
					 sleep(1);
				 }
				 std::cout << "out left" <<std::endl;
				 std::cout << "sp.GetScan(7):" << sp.GetScan(7) << ", lastobstacle:" << lastobstacle << std::endl;
				 std::cout << "sp.GetScan(0):" << sp.GetScan(0) <<std::endl;
			 }



		 }
		 else
		 {
			 turnSpeed = 0;
			 forwardSpeed = 0.2;

		 }



		 	pp.SetSpeed(forwardSpeed,  dtor(turnSpeed));


	}
	return 0;

}
void AvoidObstacles(double *forwardSpeed, double *turnSpeed,int *angle, LaserProxy &lp)
{
      //will avoid obstacles closer than 40cm
      double avoidDistance = 0.8;
      //will turn away at 60 degrees/sec
      int avoidTurnSpeed = 90;
      int side1;
      int side2;
      if (lp[*angle] < avoidDistance)
      {
    	  side1 = (*angle + 90 + 360)%360;
    	  side2 = (*angle - 90 + 360)%360;
    	 if (lp[side1] < lp[side2])
    	 {
    		 avoidTurnSpeed = -1 * avoidTurnSpeed;
    		 //*angle = side2;
    		 *forwardSpeed =0.1;
    	 }
    	 else
    	 {
    		 *forwardSpeed =0.1;
    		 //*angle = side1;
    		 *turnSpeed = avoidTurnSpeed;
    	 }
      }
      else
      {
    	  *forwardSpeed = 0.5;
    	  *turnSpeed = 0;
      }
/**
      //left corner is sonar no. 2
      //right corner is sonar no. 3
      if(sp[2] < avoidDistance)
      {

            *forwardSpeed = 0;
            //turn right
            *turnSpeed = (-1)*avoidTurnSpeed;
            return;
      }
      else if(sp[3] < avoidDistance)
      {

            *forwardSpeed = 0;
            //turn left
            *turnSpeed = avoidTurnSpeed;
            return;
      }
      else if( (sp[0] < avoidDistance) || (sp[1] < avoidDistance))
      {
            //back off a little bit
            *forwardSpeed = -0.2;
            *turnSpeed = avoidTurnSpeed;
            return;
      }
      else
      {
    	  *forwardSpeed = 0.5;
		  *turnSpeed = 0;
      }
      **/
      return; //do nothing
}



