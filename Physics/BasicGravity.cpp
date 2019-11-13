#include "BasicGravity.h"
#include "../General/Sprite.h"
#define PI 3.14159265

#define G .00000000006674

constexpr double MAX_SPEED = 3;
constexpr double MAX_DELTAV = 2;

/*
constexpr int ZONE_WIDTH = 3840; 
constexpr int ZONE_HEIGHT = 2160;
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int BOX_WIDTH = 20;
constexpr int BOX_HEIGHT = 20;*/

//movement is handled by increasing and decreasing the thrust (acceleration) in a particular direction and is capped by a max speed and acceleration
double speedX = 0;
double speedY = 0;
double deltaX = 0;
double deltaY = 0;
float playerX = 0;
float playerY = 0;
float bodyX = 0;
float bodyY = 0;
SDL_Point playerCenter;
SDL_Point bodyCenter;
double pointDistance;
float pointAngle;
float pointSlope;
long mass1 = 20000;
long mass2 = 4385000000;

// function to handle gravitational pull
//want max to be like 1 m/frame^2 min to be 0
std::vector<float> calculateGravityPull(Sprite &playerent,  std::vector<Sprite*> &osSprite){
	playerX = playerent.getTrueX() + playerent.getW()/2.0;
	playerY = playerent.getTrueY() + playerent.getH()/2.0;
	float gravX = 0.0;
	float gravY = 0.0;
	for(auto bodyent : osSprite)
	{	
		bodyX = bodyent->getTrueX() + bodyent->getW()/2.0;
		bodyY = bodyent->getTrueY() + bodyent->getH()/2.0;
		if(bodyent->getRenderOrder() ==2)
		{
			//make fix this
			pointSlope = (bodyY - playerY)/(bodyX - playerX);
			pointAngle = atan(pointSlope);
			if(playerX > bodyX)
			{
				pointAngle += 3.1415926;
			}
			std::cout << "angle: " << pointAngle * 180/ 3.14<< std::endl;
			float grav = 100000/((bodyX-playerX)*(bodyX-playerX)*1.0 + (bodyY-playerY)*(bodyY-playerY)*1.0);
			std::cout << "grav: " << grav << std::endl;
			gravX += grav*cos(pointAngle);
			gravY += grav*sin(pointAngle);
		}
	}
	 
	return {gravX, gravY};
}

void updatePositionGrav(Sprite &ent, std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT){

	speedX += deltaX;
	speedY += deltaY;
	
	if(speedX >MAX_SPEED)
	{
		speedX = MAX_SPEED;
	}
	else if(speedX < -MAX_SPEED)
	{
		speedX = -MAX_SPEED;
	}

	if(speedY >MAX_SPEED)
	{
		speedY = MAX_SPEED;
	}
	else if(speedY < -MAX_SPEED)
	{
		speedY = -MAX_SPEED;
	}
	
	
	
	ent.setX(ent.getX() + (int)speedX);
	//std::cout << "Things work up until here?" << std::endl;
	if(ent.getX() < 0 
		|| (ent.getX() + ent.getW() > ZONE_WIDTH) 
		|| ent.check_all_collisions(ent.getDrawBox(), osSprite)){

		ent.setX(ent.getX() - (int)speedX);
	}
	ent.setY(ent.getY() + (int)speedY);
	if(ent.getY() < 0 
		|| (ent.getY() + ent.getH() > ZONE_HEIGHT) 
		|| ent.check_all_collisions(ent.getDrawBox(), osSprite)){

		ent.setY(ent.getY() - (int)speedY);
	}

	std::cout << "x: " << ent.getX()  << std::endl;	
	std::cout << "y: " << ent.getY()  << std::endl;
	std::cout << "x speed: " << speedX  << std::endl;	
	std::cout << "y speed: " << speedY  << std::endl;

	
}

