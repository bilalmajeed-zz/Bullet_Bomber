//CLASS USED FOR EVERYTHING BULLET RELATED

#pragma once

#include "VisibleGameObject.h"
#include "PlayerShip.h"

#include <assert.h>

class Bullet : public VisibleGameObject
{
public:
	//CONSTRUCTOR
	Bullet(float speed, int damage, PlayerShip & p, bool realBullet);

	//DERVIED
	void draw(sf::RenderWindow & window);

	//OVERLOADED
	virtual void update();

	//data members
	bool m_used;
	bool m_real;

private:
	//private memebers
	float m_speed;
	int m_damage;
};