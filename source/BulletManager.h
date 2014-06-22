//CLASS USED TO MANAGE THE BULLETS AS ONE OBJECT
//no constructor

#pragma once

#include "Bullet.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "StatUpdate.h"
#include "SFML\Audio.hpp"

#include <vector>
#include <iostream>
using namespace std;

class BulletManager
{

public:
	void spawn(float speed, PlayerShip & p, bool realBullet); //to spawn new bullets automatically

	void update(); //to update the all the bullets
	void draw(sf::RenderWindow & window); //to draw all the bullets to the screen
		
	vector<Bullet*> & getBullets(); //function to return the list of bullets 

	

	void clear(); //clears the vector when resetting the game;

private:
	vector<Bullet*> bullets; //vector containing pointers of bullet objects

	//CONSTANTS
	const static int SCREEN_WIDTH = 500;
	const static int SCREEN_HEIGHT = 750;

	const static int SCREEN_LEFT_POS = 50;
	const static int SCREEN_BOTTOM_POS = 648;
	const static int SCREEN_TOP_POS = 0;
	const static int SCREEN_RIGHT_POS = 449;
};