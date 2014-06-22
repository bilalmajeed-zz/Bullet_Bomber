#include "EnemyManager.h"

EnemyManager::EnemyManager(string filename):
	fn(filename) //set the filename as the one passed in
{
}

void EnemyManager::clear()
{
	vector<EnemyShip*>::iterator clearIter;

	//frees up the space on the heap
	for(clearIter = ships.begin(); clearIter != ships.end(); ++clearIter)
	{
		delete * clearIter;
		*clearIter = 0;
	}
	ships.clear();//delete all the vectors
}

void EnemyManager::create(int num, int range)
{
	bool positionGood; //used to define if the intial position of the enemies is good or not
					   //depends if the enemies overlaps or not

	for(int i = 1; i <= num; i++) //do this loop for the number of ships specified and passed in
	{
		EnemyShip * eShip = new EnemyShip(fn); //make a new enemy on the heap
		
		//randomly calculate the y coordinate postion
		int y = rand(); 
		y = (y % range);

		positionGood = false; //intial positon is automatically false, will check after
		
		while(positionGood == false) //do this while the position is bad
		{		
			//randomly calculate the x coordinate position, while keeping the y value constant
			int x = rand();
			x = 66 + (x % (SCREEN_RIGHT_POS) + (SCREEN_LEFT_POS));

			//this code will make sure the bombers stay in the screen area
			if (x > 433)
				x = x-433 + 66;
			
			//set the position with the x,y values generated
			eShip->setPosition(static_cast<float>(x), -(static_cast<float>(y)));
			
			eShip->setupCollisionBoundaries("enemy"); //setup the collision boundaries for this new ship
													// to check if the new ship collides (overlaps) with other ships
		
			vector<EnemyShip*>::iterator positionIter;
			
			//----------------------------------------------------------------------------------------------------------//
			//IF the vector is empty, it means this the first ship, so no possible way to overlap
			//therefore no checking is required
			//ELSE go through each enemy ship and check for collisions, if there is no collision then 
			//make the position good else make it false and then repeat this loop again and generate new x values

			if(ships.empty())
			{
				ships.push_back(eShip);
				positionGood = true;
			}
			else
			{
				for(positionIter = ships.begin(); positionIter != ships.end(); ++positionIter)
				{
					(*positionIter)->setupCollisionBoundaries("enemy"); 

					if ((eShip->checkCollision(*(*positionIter))))
					{	
						if (num < 30) //sets a limit of having only 30 ships on the screen at once
							positionGood = false; //collision -> position bad
						break;
					}
					else
						positionGood = true; //no collision -> position good
				}
				//IF position is good then add the enemy to the vector
				if(positionGood)
					ships.push_back(eShip); 
			}
			//----------------------------------------END OF IF STATEMENT-----------------------------------------------------//
		}
		//--------------------------------------------END OF WHILE LOOP---------------------------------------------------------------------//
	}
}

int EnemyManager::updateAll(int diffNum, int range)
{
	//go through each enemy and
	//IF the enemy is in the game area THEN update the enemy
	//ELSE delete the enemy, as they are off the screen
	int passedPenalty = 0;
	vector<EnemyShip*>::iterator updateIter;
	if(!ships.empty())
	{
		for(updateIter = ships.begin(); updateIter != ships.end();)
		{		
			if ((*(*updateIter)).getPosition().y <= SCREEN_BOTTOM_POS)
			{
				(*(*updateIter)).update();
				++updateIter;
			}
			else
			{					
				delete * updateIter; //delete pointer value
				*updateIter = 0; //set the pointer value to 0 (null)
				updateIter = ships.erase(updateIter); //point to a null address
				
				passedPenalty += 5; //increase the penalty for when it passes the player	
			}
		}
	}
	else
		create(diffNum, range); //if the vector does happen to be empty then make 
						//more enemies with the difficuly number that is passed in
	
	return passedPenalty; //return the total penalty
}

void EnemyManager::drawAll(sf::RenderWindow & window)
{
	//go through each enemy and draw each one

	vector<EnemyShip*>::iterator drawIter;
	if(!ships.empty())
		for(drawIter = ships.begin(); drawIter != ships.end(); ++drawIter)
			(*drawIter)->draw(window);
}

vector<EnemyShip*> & EnemyManager::getEnemies()
{
	return ships; //return a reference to the vector of enemy ships
}


