#include "OptionsMenu.h"

OptionsMenu::MenuResult OptionsMenu::show(sf::RenderWindow& window)
{
	//Setup clickable regions

	//Sound soundbutton item coordinates
	MenuItem soundButton;
	soundButton.rect.top = 391;
	soundButton.rect.height = 456;
	soundButton.rect.left = 153;
	soundButton.rect.width = 349;
	soundButton.action = Sound;

	//Instructionsbutton menu item coordinates
	MenuItem instructionsButton;
	instructionsButton.rect.top = 482;
	instructionsButton.rect.height = 547;
	instructionsButton.rect.left = 153;
	instructionsButton.rect.width = 349;
	instructionsButton.action = Instructions;

	//Back backbutton item coordinates
	MenuItem backButton;
	backButton.rect.top = 571;
	backButton.rect.height = 636;
	backButton.rect.left = 153;
	backButton.rect.width = 349;
	backButton.action = Back;

	//add all the buttons to the list of menuItems
	menuItems.push_back(soundButton);
	menuItems.push_back(instructionsButton);
	menuItems.push_back(backButton);

	return GetMenuResponse(window); //return the action of the button clicked on
}

OptionsMenu::MenuResult OptionsMenu::HandleClick(int x, int y)
{
	//check what button clicked on and return its action
	//else return the state nothing
	
	std::list<MenuItem>::iterator it;

	for ( it = menuItems.begin(); it != menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if( menuItemRect.height > y 
			&& menuItemRect.top < y 
			&& menuItemRect.left < x 
			&& menuItemRect.width > x)
				return (*it).action;
	}

	return Nothing;
}

OptionsMenu::MenuResult  OptionsMenu::GetMenuResponse(sf::RenderWindow& window)
{
	//EITHER get the button clicked on or use the exit button to exit the menu

	sf::Event menuEvent;
	while(true)
		while(window.pollEvent(menuEvent))
		{
			if(menuEvent.type == sf::Event::MouseButtonPressed)
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);

			if(menuEvent.type == sf::Event::Closed)
				return Exit;
		}
}