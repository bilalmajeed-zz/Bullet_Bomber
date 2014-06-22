//CLASS USED FOR MANAGING THE ENEMIES AS ONE OBEJCT

#pragma once 

#include "EnemyShip.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class EnemyManager
{
public:
	//CONSTRUCTOR
	EnemyManager(string filename);
	
	void create(int num, int range); //to create enemeies with respect to the number
	
	int updateAll(int diffNum, int range); //update all the enemies
	void drawAll(sf::RenderWindow & window); //draw all the enemies

	vector<EnemyShip*> & getEnemies(); //return a reference to the list of enemies

	void clear(); //clears the enemy vector when resetting the game

private:
	vector<EnemyShip*> ships; //vector of enemies
	string fn; //used to hold the path to the enemies image

	//CONSTANTS
	const static int SCREEN_WIDTH = 500;
	const static int SCREEN_HEIGHT = 750;

	const static int SCREEN_LEFT_POS = 50;
	const static int SCREEN_BOTTOM_POS = 648;
	const static int SCREEN_TOP_POS = 0;
	const static int SCREEN_RIGHT_POS = 449;
};