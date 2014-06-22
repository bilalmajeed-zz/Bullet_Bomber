//GENERIC CLASS used by every object that gets displayed on the screen

#pragma once

#include "SFML\Graphics.hpp"

#include <iostream>
#include <string>
using namespace std;

class VisibleGameObject
{
public:
	VisibleGameObject(); //constructor

	void load(string filename); //load image files
	void draw(sf::RenderWindow & window); //draw the objects to the screen
	
	//to be overloaded
	virtual void update(); //update the objects
	
	void setPosition(float x, float y); //set position of the object
	sf::Vector2f getPosition() const; //get positon of the object
	
	void setupCollisionBoundaries(string object); //setup collision boundaries for objects
	bool checkCollision(VisibleGameObject & ship); //check collision for the objects
	
	sf::Sprite & getSprite(); //get sprite
	float bottom, top, left, right; //data members

protected:
	//CONSTANTS
	const static int SCREEN_LEFT_POS = 50;
	const static int SCREEN_BOTTOM_POS = 648;
	const static int SCREEN_TOP_POS = 0;
	const static int SCREEN_RIGHT_POS = 449;

	const static int SCREEN_WIDTH = 500;
	const static int SCREEN_HEIGHT = 750;

	virtual bool isLoadedAccess() const;

private:
	//data members
	sf::Texture texture;
	sf::Sprite sprite;
	string filename;
	bool isLoaded;
};