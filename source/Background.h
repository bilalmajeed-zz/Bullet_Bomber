//CLASS USED FOR DRAWING THE BACKGROUND

#pragma once

#include "VisibleGameObject.h"

class Background : public VisibleGameObject
{
public:
	//OVERLOADED
	virtual void draw(sf::RenderWindow & window);
};