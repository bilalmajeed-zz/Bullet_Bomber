#include "Bullet.h"

//constructor
Bullet::Bullet(float speed, int damage, PlayerShip & p, bool realBullet):
	m_speed(speed), //set speed
	m_damage(damage), //damage
	m_used(false), //if its used or not
	m_real(realBullet) //if its a real bullet or not
{
	load("images//bullet.png"); //loads the bullet image
	assert(isLoadedAccess()); //try and catch statement
	
	getSprite().setOrigin(2,3); //set the orgin of the bullets in the middle

	setPosition(p.getPosition().x, p.getPosition().y); //set the position
}

void Bullet::draw(sf::RenderWindow & window)
{
	//if the bullet is a real one then draw it otherwise do not
	if(m_real)
		VisibleGameObject::draw(window); //draw the bullet
}

void Bullet::update()
{
	//CALLED EVERY GAME LOOP
	//moves the bullet up with a constant speed and then updates its collisions boundaries
	getSprite().move(0.0f, -m_speed);
	setupCollisionBoundaries("bullet");
}
