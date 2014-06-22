#include "VisibleGameObject.h"

//constructor
VisibleGameObject::VisibleGameObject():
	isLoaded(false) //isloaded is false
{}

//LOAD the image for the object
void VisibleGameObject::load(string image)
{
	//try and catch statement 

	if(!texture.loadFromFile(image)) //try loading 
		cout << "ERROR" << endl;
	else //if succesful set the image
	{
		filename = image;
		sprite.setTexture(texture);
		isLoaded = true;
	}
}

//draw the object to the screen
void VisibleGameObject::draw(sf::RenderWindow & window)
{
	if(isLoaded)
		window.draw(sprite);
}

//to be overloaded
void VisibleGameObject::update()
{}

//set position of the object
void VisibleGameObject::setPosition(float x, float y)
{
	if(isLoaded)
		sprite.setPosition(x, y);
}

//return  the position of the object
sf::Vector2f VisibleGameObject::getPosition() const
{
	if(isLoaded)
		return sprite.getPosition();

	return sf::Vector2f();
}

//setup the collison boundaries
void VisibleGameObject::setupCollisionBoundaries(string object)
{
	if(object == "player")
	{
		//PLAYER HITBOX AREA
		//3 pixels from each direction from the center
		top = getPosition().y - 3;
		bottom = getPosition().y + 3;
		left = getPosition().x - 3;
		right = getPosition().x + 3;
	}
	else if(object == "enemy")
	{
		//ENEMY HITBOX AREA
		//the entire ship

		top = getPosition().y - 16;
		bottom = getPosition().y + 16;
		left = getPosition().x - 16;
		right = getPosition().x + 16;
	}
	else if(object == "bullet")
	{
		//BULLET HITBOX AREA
		//the entire bullet

		top = getPosition().y - 2;
		bottom = getPosition().y + 2;
		left = getPosition().x - 1;
		right = getPosition().x + 1;
	}
}

//check the collisions of the object with another object
bool VisibleGameObject::checkCollision(VisibleGameObject & ship)
{
	if(right < ship.left || left > ship.right|| 
		top > ship.bottom || bottom < ship.top)
		return false;
	return true;
}

//return sprite (private)
sf::Sprite & VisibleGameObject::getSprite() 
{ 
	return sprite; 
}
//return isLoaded (protected)
bool VisibleGameObject::isLoadedAccess() const
{
	return isLoaded;
}
