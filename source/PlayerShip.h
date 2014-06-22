//CLASS USED FOR THE PLAYER OBJECT

#pragma once

//EVERYTHING THAT NEEDS TO BE INCLUDED
#include "VisibleGameObject.h"
#include "GenericPlayer.h"
#include <iostream>
#include <assert.h>
using namespace std;

//derive this class from the visible game object and genericplayer classes
class PlayerShip : public VisibleGameObject, public GenericPlayer
{
public:
	PlayerShip(); //constructor

	//OVERLOADED FROM VISIBLE GAME OBEJCT
	virtual void update();
	

	//--------------DERIVED FUNCTIONS----------------------//

	//	void VisibleGameObject::draw(sf::RenderWindow window);

	//	void GenericPlayer::updateHealth(float health);
	//	void GenericPlayer::updateFireRate(int fireRate);
	//	void GenericPlayer::updateSpeed(int speed);

	//-----------------------------------------------------//

};