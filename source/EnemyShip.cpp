#include "EnemyShip.h"

EnemyShip::EnemyShip(string filename)
{
	//PROTECTED DATA MEMBERS FROM THE GENERIC PLAYER CLASS
	m_health = 100.0f;
	m_fireRate = 0;
	m_speed = 5.0f;
	
	load(filename); //load the image and set the sprite and texture
	assert(isLoadedAccess()); //try and catch for the image loading

	getSprite().setOrigin(16,16); //set orgins to the middle of the ship
}

void EnemyShip::update()
{
	//CALLED EVERY GAME LOOP
	//moves the enemy down at a constant speed and then sets its collision boundaries
	
	getSprite().move(0.0f, m_speed);
	setupCollisionBoundaries("enemy");
}

//--------------DERIVED FUNCTIONS----------------------//

//	void VisibleGameObject::draw(sf::RenderWindow window);

//	void GenericPlayer::updateHealth(float health);
//	void GenericPlayer::updateFireRate(int fireRate);
//	void GenericPlayer::updateSpeed(int speed);

//-----------------------------------------------------//