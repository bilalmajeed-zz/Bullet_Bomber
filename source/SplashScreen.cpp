// The Splashscreen

#include "SplashScreen.h"

bool SplashScreen::show(sf::RenderWindow & window)
{
	//declare variables
	sf::Texture sTexture; 
	sf::Sprite splashImage;

	//load the texture file
	if(!sTexture.loadFromFile("images//splash.png"))
		cout << "ERROR" << endl;

	//set the texture on the sprite
	splashImage.setTexture(sTexture);
	
	//deaw the background image
	window.draw(splashImage);
	window.display();

	//check if a button was clicked or if a key was pressed and if it was then return TRUE else FALSE
	sf::Event e;
	while(true)
		while(window.pollEvent(e))
		{
			if(e.type == sf::Event::KeyPressed || e.type == sf::Event::MouseButtonPressed)
				return true; //true when key pressed or mouse button pressed
			if(e.type == sf::Event::Closed)
				return false; //false when window closed
		}
}
    