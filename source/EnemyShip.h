//CLASS USED FOR THE ENEMY SHIP OBJECTS

#pragma once

#include "VisibleGameObject.h"
#include "GenericPlayer.h"

#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <ctime>
using namespace std;

//DEVRIVE THIS CLASS FROM BOTH GENERIC CLASSES
class EnemyShip : public VisibleGameObject, public GenericPlayer
{
public:
	//CONSTRUCTOR
	EnemyShip(string filename);

	//OVERLOADED FROM VISIBLE GAME OBEJCT
	virtual void update();

	//--------------DERIVED FUNCTIONS----------------------//

	//	void VisibleGameObject::draw(sf::RenderWindow window);

	//	void GenericPlayer::updateHealth(float health);
	//	void GenericPlayer::updateFireRate(int fireRate);
	//	void GenericPlayer::updateSpeed(int speed);

	//-----------------------------------------------------//
};