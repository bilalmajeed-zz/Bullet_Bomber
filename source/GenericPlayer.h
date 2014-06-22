//CLASS USED AS A GENERIC CLASS FOR THE ENEMY AND PLAYER CLASSES

#pragma once

#include <iostream>
using namespace std;

class GenericPlayer
{
public:
	void updateHealth(float health); //update the health of the ship
	void updateFireRate(int fireRate);//update the firerate of the ship
	void updateSpeed(int speed); //update the speed of the ships

protected:
	//data members
	float m_health;
	int m_fireRate;
	float m_speed;
};