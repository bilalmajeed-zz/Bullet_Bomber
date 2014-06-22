#include "GenericPlayer.h"
#include <iostream>

void GenericPlayer::updateHealth(float health)
{
	m_health = health; //set health
}

void GenericPlayer::updateFireRate(int fireRate)
{
	m_fireRate = fireRate; //set firerate
}

void GenericPlayer::updateSpeed(int speed)
{
	m_speed = speed; //set speed
}