//CLASS USED FOR MANAGING KILLS, HEALTH, AND SCORE OF THE PLAYER

#pragma once

#include "VisibleGameObject.h"
#include <sstream>

class StatUpdate : public VisibleGameObject //dervied from the visiblegameobject class
{

public:
	StatUpdate(); //constructor

	//functions needed
	void difficultyChange();  //change difficulty
	int getScore(); //get the score of the player
	int getKills(); //get the # of kills by the player
	int getHealth(); //get the players health
	void reset(); //reset the score, kills, and health

	// DERIVED
	void draw(sf::RenderWindow & window); //draw the score, kills, and health text

	// UPDATE FUNCTIONS
	void scoreUpdate(string type = "normal", int increase = 0); //update score
	void killsUpdate(); //update kills
	void healthUpdate(int change); //update health


private:
	//privare data members
	int m_score;
	int m_kills;
	int m_health;
	sf::Font m_font;

};