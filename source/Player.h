#pragma once

#include "VisibleGameObject.h"
#include "GenericPlayer.h"
#include <iostream>
using namespace std;

class Player : public VisibleGameObject, public GenericPlayer
{
public:
	Player();
	~Player();

	virtual void update();
	virtual void draw(sf::RenderWindow & window);
};