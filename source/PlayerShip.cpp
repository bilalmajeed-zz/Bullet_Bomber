#include "PlayerShip.h"

//constructor
PlayerShip::PlayerShip()
{	
	//PROTECTED DATA MEMBERS FROM THE GENERIC PLAYER CLASS
	m_health = 100.0f;
	m_fireRate = 0;
	m_speed = 0;

	load("images//ship.png"); //load the player image
	assert(isLoadedAccess()); //assertion check
	getSprite().setOrigin(16,16); //set the orgin in the middle of the ship
}

//update function OVERLOADED FROM VISIBLE GAME OBEJCT
void PlayerShip::update()
{
	setupCollisionBoundaries("player");
}


//--------------DERIVED FUNCTIONS----------------------//

//	void VisibleGameObject::draw(sf::RenderWindow window);

//	void GenericPlayer::updateHealth(float health);
//	void GenericPlayer::updateFireRate(int fireRate);
//	void GenericPlayer::updateSpeed(int speed);

//-----------------------------------------------------//