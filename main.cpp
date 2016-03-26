/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>

using namespace PlayerCc;
void AvoidObstacles(double *forwardSpeed, double *turnSpeed, SonarProxy &sp);
void Wander(double *forwardSpeed, double *turnSpeed);
int main() {

	PlayerClient pc("localhost", 6665);
	LaserProxy lp(&pc);
	Position2dProxy pp(&pc);
	SonarProxy sp(&pc,0);
	double forwardSpeed, turnSpeed;
	pp.SetMotorEnable(true);
	while (true) {
		pc.Read();
				 //avoid obstacles
		 Wander(&forwardSpeed, &turnSpeed);
		AvoidObstacles(&forwardSpeed, &turnSpeed, sp);

		//set motors
		pp.SetSpeed(forwardSpeed, dtor(turnSpeed));

		/**if (lp[333] < 0.8)
		{
			pp.SetSpeed(0.0, 0.5);

		}
		else
			pp.SetSpeed(0.8, 0.0); **/
	}
	return 0;

}
void AvoidObstacles(double *forwardSpeed, double *turnSpeed, SonarProxy &sp)
{
      //will avoid obstacles closer than 40cm
      double avoidDistance = 0.2;
      //will turn away at 60 degrees/sec
      int avoidTurnSpeed = 90;

      //left corner is sonar no. 2
      //right corner is sonar no. 3
      if(sp[2] < avoidDistance)
      {
    	  std::cout << "go right" << std::endl;
            *forwardSpeed = 0;
            //turn right
            *turnSpeed = (-1)*avoidTurnSpeed;
            return;
      }
      else if(sp[3] < avoidDistance)
      {
    	  std::cout << "go left" << std::endl;
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

      return; //do nothing
}

void Wander(double *forwardSpeed, double *turnSpeed)
{
      int maxSpeed = 1;
      int maxTurn = 90;
      double fspeed, tspeed;

      //fspeed is between 0 and 10
      fspeed = rand()%11;
      //(fspeed/10) is between 0 and 1
      fspeed = (fspeed/10)*maxSpeed;

      tspeed = rand()%(2*maxTurn);
      tspeed = tspeed-maxTurn;
      //tspeed is between -maxTurn and +maxTurn

      *forwardSpeed = fspeed;
      *turnSpeed = tspeed;
}

