#include "BulletManager.h"

void BulletManager::spawn(float speed, PlayerShip & p, bool realBullet)
{
	//add a new bullet on the heap with the arguments passed in
	bullets.push_back(new Bullet(speed, 10, p, realBullet));
}

void BulletManager::update()
{
	//IF bullets are in the the game screen area then update it (move it)
	//ELSE delete that bullet, as it is no longer needed

	vector<Bullet*>::iterator iter;
	if (!bullets.empty())
		for (iter = bullets.begin(); iter != bullets.end();)
		{	
			if ((*(*iter)).getPosition().y > -10) //-200 so the bullets have a 200px wiggle room
			{
				(*(*iter)).update();
				++iter;
			}
			else
			{
				delete * iter; //delete the pointer value
				iter = bullets.erase(iter); //sets the pointer to a null value	
			}
		}
}

void BulletManager::draw(sf::RenderWindow & window)
{
	//go through each bullet and draw each of them

	vector<Bullet*>::iterator drawIter;

	if (!bullets.empty())
		for (drawIter = bullets.begin(); drawIter != bullets.end(); ++drawIter)
			(*(*drawIter)).draw(window);
}

vector<Bullet*> & BulletManager::getBullets()
{
	//return the vector of bullets
	return bullets;
}

void BulletManager::clear()
{
	vector<Bullet*>::iterator clearIter;

	//frees up the space on the heap
	for(clearIter = bullets.begin(); clearIter != bullets.end(); ++clearIter)
	{
		delete * clearIter;
		*clearIter = 0;
	}
	bullets.clear();//delete all the vectors
}
