#include "GameOverMenu.h"

GameOverMenu::MenuResult GameOverMenu::show(sf::RenderWindow& window)
{
	//Setup clickable regions

	//Play playAgain item coordinates
	MenuItem playAgainButton;
	playAgainButton.rect.top = 482;
	playAgainButton.rect.height = 547;
	playAgainButton.rect.left = 153;
	playAgainButton.rect.width = 350;
	playAgainButton.action = PlayAgain;

	//Exit menuButton item coordinates
	MenuItem menuButton;
	menuButton.rect.top = 571;
	menuButton.rect.height = 636;
	menuButton.rect.left = 153;
	menuButton.rect.width = 350;
	menuButton.action = Menu;
	
	//add all the buttons to the list of menuItems
	menuItems.push_back(playAgainButton);
	menuItems.push_back(menuButton);

	return GetMenuResponse(window); //return the action of the button clicked on
}

GameOverMenu::MenuResult GameOverMenu::HandleClick(int x, int y)
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

GameOverMenu::MenuResult  GameOverMenu::GetMenuResponse(sf::RenderWindow& window)
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