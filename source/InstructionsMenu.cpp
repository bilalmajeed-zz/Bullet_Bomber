#include "InstructionsMenu.h"

InstructionsMenu::MenuResult InstructionsMenu::show(sf::RenderWindow& window)
{
	//Load menu image from file
	sf::Texture mTexture;
	sf::Sprite menuImage;

	//TRY loading the image CATCH print out error to console
	if(!mTexture.loadFromFile("images//instructions.png"))
		cout << "ERROR" << endl;

	menuImage.setTexture(mTexture); //set the texture to sprite

	//Setup clickable regions
	//Back menu item coordinates
	MenuItem backButton;
	backButton.rect.top = 571;
	backButton.rect.height = 636;
	backButton.rect.left = 153;
	backButton.rect.width = 349;
	backButton.action = Back;

	//add all the buttons to the list of menuItems

	menuItems.push_back(backButton);

	//draw the menu image, the background
	window.draw(menuImage);
	window.display();

	return GetMenuResponse(window); //return the action of the button clicked on
}

InstructionsMenu::MenuResult InstructionsMenu::HandleClick(int x, int y)
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

InstructionsMenu::MenuResult  InstructionsMenu::GetMenuResponse(sf::RenderWindow& window)
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