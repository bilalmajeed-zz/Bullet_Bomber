#include "Menu.h"

Menu::MenuResult Menu::show(sf::RenderWindow& window)
{
	//Load menu image from file
	sf::Texture mTexture;
	sf::Sprite menuImage;

	//TRY loading the image CATCH print out error to console
	if(!mTexture.loadFromFile("images//mainmenu.png"))
		cout << "ERROR" << endl;

	menuImage.setTexture(mTexture); //set the texture to sprite

	//Setup clickable regions

	//Play menu item coordinates
	MenuItem playButton;
	playButton.rect.top = 391;
	playButton.rect.height = 456;
	playButton.rect.left = 153;
	playButton.rect.width = 349;
	playButton.action = Play;

	//Options menu item coordinates
	MenuItem optionsButton;
	optionsButton.rect.top = 482;
	optionsButton.rect.height = 547;
	optionsButton.rect.left = 153;
	optionsButton.rect.width = 349;
	optionsButton.action = Options;

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.top = 571;
	exitButton.rect.height = 636;
	exitButton.rect.left = 153;
	exitButton.rect.width = 349;
	exitButton.action = Exit;

	//add all the buttons to the list of menuItems
	menuItems.push_back(playButton);
	menuItems.push_back(optionsButton);
	menuItems.push_back(exitButton);

	//draw the menu image, the background
	window.draw(menuImage);
	window.display();

	return GetMenuResponse(window); //return the action of the button clicked on
}

Menu::MenuResult Menu::HandleClick(int x, int y)
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

Menu::MenuResult  Menu::GetMenuResponse(sf::RenderWindow& window)
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