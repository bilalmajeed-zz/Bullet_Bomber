//CLASS USED TO DISPLAY THE INSTRUCTIONS MENU

#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <list>
#include "Game.h"
#include <iostream>

using namespace std;

class InstructionsMenu
{
public:
	// a enum of all the different bullets to click
	enum MenuResult { Nothing, Back, Exit };  
	 
	//make a class in a class
	struct MenuItem 
	{
		public:
			sf::Rect<int> rect;
			MenuResult action;
	};

	//return a menuresult state
	MenuResult show(sf::RenderWindow& window);

private:
	MenuResult GetMenuResponse(sf::RenderWindow& window); //gets the action of the button clicked on
	MenuResult HandleClick(int x, int y); //check if a button is clicked
	std::list<MenuItem> menuItems; // a new list of MenuItems
};