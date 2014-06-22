#include "Game.h"

//static data members 
Game::GameState 
Game::gameState = Uninitialized;

sf::RenderWindow Game::mainWindow;

Background Game::bg_bottom;
Background Game::bg_top;

PlayerShip Game::player;
EnemyManager Game::bombers("images//bomber.png");

BulletManager Game::bullets;

VisibleGameObject Game::cursor;
VisibleGameObject Game::soundOffButton;

//ALL THE DIFFERENT MENU SCREENS
VisibleGameObject Game::pause;
VisibleGameObject Game::leavingScreen;
VisibleGameObject Game::optionsScreen;
VisibleGameObject Game::instructionsScreen;
VisibleGameObject Game::gameOverScreen;
VisibleGameObject Game::redScreen60;
VisibleGameObject Game::redScreen30;

StatUpdate Game::stats; 

sf::Clock Game::clock;
sf::Music Game::menuMusic;
sf::Sound Game::bulletSound;
sf::Music Game::bgMusic;

bool Game::isPaused = false;
bool Game::isSoundOn = true;
int Game::buttonClickCount = 3; //used to see the sound off button is clicked or not
int Game::diffNum = 3; //difficulty number

//member functions
void Game::start()
{
	//if game not initialized then dont start
	if(gameState != Uninitialized)
		return;

	srand(time(NULL)); //seed the number generator
	mainWindow.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32), "Bullet Bomber", sf::Style::Titlebar | sf::Style::Close); //main window
	mainWindow.setPosition(sf::Vector2i(400,10)); //window opening position
	mainWindow.setFramerateLimit(20);

	//LOAD THE BACKGROUND
	bg_bottom.load("images//gamebg_bottom.png");
	bg_top.load("images//gamebg_top.png");
	
	//SETUP THE CURSOR/HITBOX
	cursor.load("images//cursor.png");
	cursor.getSprite().setOrigin(3,3);

	//SETUP THE SOUND OFF BUTTON SCREEN
	soundOffButton.load("images//musicOff.png");
	soundOffButton.setPosition(152,391);

	//SETUP THE PAUSE SCREEN
	pause.load("images//pause.png");
	pause.setPosition(0,0);

	//SETUP THE ABOUT TO LEAVE SCREEN
	leavingScreen.load("images//leaving.png");
	leavingScreen.setPosition(0,0);

	//SETUP THE OPTIONS SCREEN
	optionsScreen.load("images//options.png");
	optionsScreen.setPosition(0,0);

	//SETUP GAME OVER SCREEN
	gameOverScreen.load("images//exitScreen.png");
	gameOverScreen.setPosition(0,0);

	//SETUP THE INSTRUCTIONS SCREEN
	instructionsScreen.load("images//instructions.png");
	instructionsScreen.setPosition(0,0);

	//SEtup THE BLOODY SCREEN
	redScreen60.load("images//redScreen2.png");
	redScreen60.setPosition(0,0);

	redScreen30.load("images//redScreen.png");
	redScreen30.setPosition(0,0);

	//SETUP PLAYER SHIP
	player.setPosition((SCREEN_WIDTH/2),250);

	//LOAD THE MENU MUSIC
	if (!menuMusic.openFromFile("music//menumusic.ogg"))
		cout << "Could not open music file" << endl;
	menuMusic.setLoop(true);

	//LOAD THE BACKGROUND MUSIC
	if (!bgMusic.openFromFile("music//bgMusic.ogg"))
		cout << "Could not open music file" << endl;
	bgMusic.setLoop(true);

	//LOAD THE BULLET SOUND EFFECT
	if (!bulletBuffer.loadFromFile("music//bulletsound.wav"))
		cout << "Could not open music file" << endl;
	
	bulletSound.setBuffer(bulletBuffer);
	bulletSound.setVolume(25);

	gameState = Game::ShowingSplashScreen; //open the splash screen

	//if game is not over then go to the game loop
	while(!isExiting())
		GameLoop();

	mainWindow.close(); //close the window after the game is over
}

bool Game::isExiting()
{
	//is game state is exiting then return true, else return false
	if (gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{
	//check the game states
	switch(gameState)
	{
//--------------------------------------------------------------------------------------------------------------------//
		//if showing the MAIN WINDOW
		case Game::ShowingMainMenu:
			{
				while(true)
				{
					showMenu();
					break;
				}
				break;
			}
//--------------------------------------------------------------------------------------------------------------------//
		//if showing SPLASH SCREEN
		case Game::ShowingSplashScreen:
			{
				showSplashScreen();
				break;
			}
//--------------------------------------------------------------------------------------------------------------------//
		//if game is PLAYING
		case Game::Playing:
			{	
				menuMusic.stop();
				
				if(isSoundOn)
					bgMusic.play();
				else
					bgMusic.pause();

				sf::Time elaspedTime = clock.restart(); //restart the fps clock
			
				bombers.create(4, stats.getKills() + 200); //spawn four bombers at the start of the game
				
				//set up a few variables needed for the game
				sf::Event currentEvent; //sets up the event variable
				int tempFirerate = 0; 
				bool dead = false;
				bool killEnemy = false;
				int penalty;
				while (true)
				{
					if(mainWindow.pollEvent(currentEvent)) //gets the event
					{
						mainWindow.setMouseCursorVisible(false); //hides the cursor
						mainWindow.clear(sf::Color(0,0,0)); //makes the bg black 

						//if mouse is moved then move the player ship to that position
						if(currentEvent.type == sf::Event::MouseMoved)
						{
							if(currentEvent.mouseMove.x >= SCREEN_LEFT_POS
								&& currentEvent.mouseMove.y <= SCREEN_BOTTOM_POS
								&& currentEvent.mouseMove.x <= SCREEN_RIGHT_POS)
							{
								cursor.setPosition(static_cast<float>(currentEvent.mouseMove.x), static_cast<float>(currentEvent.mouseMove.y));
								player.setPosition(static_cast<float>(currentEvent.mouseMove.x), static_cast<float>(currentEvent.mouseMove.y));
							}
						}

						//if you click the exit button in the window then the game state is exiting
						if(currentEvent.type == sf::Event::Closed)
						{
							gameState = Game::Exiting;
							break;
						}
						
						if(currentEvent.type == sf::Event::KeyPressed)
							
							//if the P key is pressed then pause the game
							if(currentEvent.key.code == sf::Keyboard::P)
							{
								gameState = Game::Paused;
								break;
							}

							//if the ESCAPE key is pressed then display the leaving message
							if(currentEvent.key.code == sf::Keyboard::Escape)
							{
								gameState = Game::Leaving;
								break;
							}
					}
					
					elaspedTime = clock.restart();

					vector<EnemyShip*> & listOfBombers = bombers.getEnemies();
					vector<EnemyShip*>::iterator enemyIter;
					
					vector<Bullet*> & listOfBullets = bullets.getBullets();
					vector<Bullet*>::iterator bulletIter;
			
					for(enemyIter = listOfBombers.begin(); enemyIter != listOfBombers.end(); ++enemyIter)
					{
						//	move enemies 90 frames per second
						(*(*enemyIter)).updateSpeed(static_cast<int>(elaspedTime.asSeconds() * 90));
						 
						//check for player-enemy collision
						if(player.checkCollision((*(*enemyIter))))
						{							
							killEnemy = true;
							stats.healthUpdate(10); //take off 10 hp from the player if it collides with the enemy
							
							if (stats.getHealth() <= 0)
								dead = true; //if the health is less than 0, kill the player
						}
							
						//check for enemy-bullet collision
						for(bulletIter = listOfBullets.begin(); bulletIter != listOfBullets.end(); ++bulletIter)
						{
							if(!listOfBullets.empty())
							{
								//check if a bullet hit a enemy or not
								if((*(*bulletIter)).checkCollision((*(*enemyIter))) && (*(*bulletIter)).getPosition().y >= 0)
								{
									stats.killsUpdate(); //update kills
									stats.scoreUpdate("kills", 100); //add 100 to the score

									//every 8 kills increase the difficulty
									if (stats.getKills()%8 == 0 && stats.getKills() > 0)
									{
											diffNum += 1;
									}

									killEnemy = true; //kill the enemy after the bullet hits it
									(*bulletIter)->m_used = true; //flag the bullet as used
								}
							}
						}

						//if the enemy is flagged as killed then delete that pointer from  the vector of bombers
						if(!listOfBombers.empty() && killEnemy == true)
						{
							killEnemy = false;
						
							//deletes the pointer from the vector without memeory leaks
							delete * enemyIter;
							*enemyIter = 0;
							enemyIter = listOfBombers.erase(enemyIter);
							
							break;
						}
					}
					
					++tempFirerate;
					if (tempFirerate == 10)
					{
						//if the sound is on then play the bullet shooting sound effect when spawning a new bullet
						//else spawn the bullet without playing the sound
						if(isSoundOn)
						{
							bulletSound.stop();
							//	move bullets 200 frames per second
							bullets.spawn(static_cast<float>(elaspedTime.asSeconds() * 200), player, true);
							tempFirerate = 0;
							bulletSound.play();
						}
						else
						{
							//	move bullets 200 frames per second
							bullets.spawn(static_cast<float>(elaspedTime.asSeconds() * 200), player, true);
							tempFirerate = 0;
						}
					}			

					//for each bullet if it is flageed as used then delete it from the heap
					if(!listOfBullets.empty())
					{
						vector<Bullet*>::iterator bulletDeleteIter;
						for(bulletDeleteIter = listOfBullets.begin(); bulletDeleteIter != listOfBullets.end();)
						{
							if((*(*bulletDeleteIter)).m_used == true)
							{
								delete * bulletDeleteIter;
								*bulletDeleteIter = 0;
								bulletDeleteIter = listOfBullets.erase(bulletDeleteIter);
							}
							else
								++bulletDeleteIter;
						}
					}

					// UPDATES EVERYTHING
					stats.scoreUpdate();
					bullets.update();
					player.update();

					//if the bombers passes you and is no dead then a penality is applied
					penalty = bombers.updateAll(diffNum, stats.getKills() + 200);
					if (penalty > 0)
					{
						stats.healthUpdate(penalty);
						if(stats.getHealth() <= 0)
							dead = true;
					}

						
					//DRAWS EVERYTHING
					bg_bottom.draw(mainWindow);
					
					bullets.draw(mainWindow);
					player.draw(mainWindow);
					cursor.draw(mainWindow);
					bombers.drawAll(mainWindow);
					
					bg_top.draw(mainWindow);
					
					stats.draw(mainWindow);

					if(stats.getHealth() <= 50 && stats.getHealth() > 10)
						redScreen60.draw(mainWindow);
					else if(stats.getHealth() <= 10)
						redScreen30.draw(mainWindow);

					mainWindow.display();

					//IF THE PLAYER IS DEAD THEN GO TO THE GAME OVER SCREEN
					if (dead)
					{
						gameState = Game::GameOver;
						break;
					}
				}
				break;
			}
//--------------------------------------------------------------------------------------------------------------------//
		//IF THE GAME IS PAUSED
		case Game::Paused:
			{
				bgMusic.pause();
				while (true)
				{
					mainWindow.clear(sf::Color::Transparent);
					pause.draw(mainWindow);
					mainWindow.display();

					sf::Event pauseEvent;		//sets up event variable
					if(mainWindow.pollEvent(pauseEvent)) //gets the event
						if(pauseEvent.type == sf::Event::KeyPressed)
							if(pauseEvent.key.code == sf::Keyboard::P)
								gameState = Game::Playing;
					break;
				}
				break;
			}
//--------------------------------------------------------------------------------------------------------------------//
		//IF SHOWING OPTIONS SCREEN
		case Game::ShowingOptions:
			{
				buttonClickCount = 4;
				showOptions();
				break;
			}
//--------------------------------------------------------------------------------------------------------------------//
		//IF SHOWING INSTRUCTIONS SCREEN
		case Game::ShowingInstructions:
			{
				showInstructions();	
				break;
			}
//--------------------------------------------------------------------------------------------------------------------//
		//IF SHOWING THE GAME OVER SCREEN
		case Game::GameOver:
			{
				int freezeTime = 0;
				while(freezeTime <= 10000000)
				{
					freezeTime++;
				}
				showGameOverScreen();
				break;
			}
//--------------------------------------------------------------------------------------------------------------------//
		//IF SHOWING THE GAME LEAVING WARNING SCREEN
		case Game::Leaving:
			{
				bgMusic.pause();
				mainWindow.clear(sf::Color::Transparent);
				leavingScreen.draw(mainWindow);
				mainWindow.display();
				
				sf::Event leaveEvent;
				if(mainWindow.pollEvent(leaveEvent))
					if(leaveEvent.type == sf::Event::KeyPressed)
					{
						if(leaveEvent.key.code == sf::Keyboard::Return)
							gameState = Game::Playing;
						if(leaveEvent.key.code == sf::Keyboard::Escape)
						{
							resetting();
							gameState = Game::ShowingMainMenu;
							mainWindow.setMouseCursorVisible(true);
						}
					}
			}
//--------------------------------------------------------------------------------------------------------------------//
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------//


//SHOWING SPLASH SCREEN FUNCTION
void Game::showSplashScreen()
{
	SplashScreen splash; //splash screen object

	if(splash.show(mainWindow))
		gameState = Game::ShowingMainMenu;
	else
		gameState = Game::Exiting;
}

//SHOWING MAIN MENU FUNCTION
void Game::showMenu()
{
	mainWindow.clear();
	Menu mainMenu; //main menu object

	//IF sound is on, play music ELSE pause music
	if (isSoundOn)
		menuMusic.play();
	else
		menuMusic.pause();

	Menu::MenuResult result = mainMenu.show(mainWindow);

	switch(result)
	{
	case Menu::Exit:
		gameState = Game::Exiting; //if result is exit button
		break;
	case Menu::Play: //if result is play button
		gameState = Game::Playing; 
		break;
	case Menu::Options: //if result is options button
		gameState = Game::ShowingOptions;
		menuMusic.pause();
		break;
	}
}

//SHOWING INSTRUCTONS FUNCTION
void Game::showInstructions()
{
	mainWindow.clear();
	InstructionsMenu instrutMenu; //instruction menu button

	InstructionsMenu::MenuResult result = instrutMenu.show(mainWindow);

	switch(result)
	{
	case InstructionsMenu::Back: //if result is the back button
		gameState = Game::ShowingOptions;
		break;
	case InstructionsMenu::Exit: //if the result is the exit button
		gameState = Game::Exiting;
		break;
	}
}

//SHOWING GAME OVER SCREEN FUNCTION
void Game::showGameOverScreen()
{
	mainWindow.setMouseCursorVisible(true); //cursor will be visible
	GameOverMenu overMenu; //gameover menu object

	//new font
	sf::Font font;
	if (!font.loadFromFile("gameOverFont.TTF"))
		cout << "Could not load Font file" << endl;

	//convert int to string to displau to screen
	string strScore;
	ostringstream scoreConvert;
	scoreConvert << stats.getScore();
	strScore = scoreConvert.str();

	//setup the text/font
	sf::Text score(strScore, font, 50);
	score.setColor(sf::Color(255,255,255));
	
	//center score text
	sf::FloatRect scoreRect = score.getLocalBounds();
	score.setOrigin(scoreRect.left + scoreRect.width/2.0f, scoreRect.top + scoreRect.height/2.0f);
	score.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f));

	//draw text and background
	mainWindow.clear();
	gameOverScreen.draw(mainWindow);
	mainWindow.draw(score);
	mainWindow.display();

	GameOverMenu::MenuResult result = overMenu.show(mainWindow);

	switch(result)
	{
	case GameOverMenu::PlayAgain: //if result is the play again button
		resetting();
		gameState = Game::Playing; 
		break;
	case GameOverMenu::Menu: //if result is menu button
		resetting();
		gameState = Game::ShowingMainMenu;
		break;
	case GameOverMenu::Exit: //if result is exit button
		gameState = Game::Exiting;
		break;
	}
}

//SHOWING THE OPTIONS SCREEN FUNCTION
void Game::showOptions()
{
	bool breakOut = false;
	while(!breakOut)
	{		
		if(buttonClickCount == 3 || buttonClickCount == 4) //if button click count is 4 or three 
															//means this is first time entering the options screen
															//or that it just came from the main menu
		{
			mainWindow.clear(); //clear the screen
			optionsScreen.draw(mainWindow); //draw the options screen background
			mainWindow.display(); //display to screen
			buttonClickCount = 1;
		}

		if(!isSoundOn) //if sound is off then do this
		{
			menuMusic.pause(); //pause the music
			
			soundOffButton.draw(mainWindow); //draw the off button 
			mainWindow.display();
			
			if (buttonClickCount != 2 && buttonClickCount == 4)
				isSoundOn = true;
		}
		else
			menuMusic.play(); //else play the music
		
		OptionsMenu optionMenu; //options menu object

		OptionsMenu::MenuResult result = optionMenu.show(mainWindow);

		switch(result)
		{
		case OptionsMenu::Back: //if result is back button
			breakOut = true;
			menuMusic.pause();
			gameState = Game::ShowingMainMenu;
			break;
		case OptionsMenu::Instructions: //if result is instructions button
			breakOut = true;
			gameState = Game::ShowingInstructions;
			break;
		case OptionsMenu::Exit: //if result is exit button
			breakOut = true;
			gameState = Game::Exiting;
			break;
		case OptionsMenu::Sound: //if result is sound button
			if(buttonClickCount == 1)
			{
				isSoundOn = false; //turn off music
				
				soundOffButton.draw(mainWindow); //draw the off button
				mainWindow.display();
				
				buttonClickCount = 2;
				break;
			}
			else
			{
				//draw the background without the button
				mainWindow.clear();
				optionsScreen.draw(mainWindow);
				mainWindow.display();

				buttonClickCount = 1;
				isSoundOn = true; //turn on the music
				break;
			}
		}
	}
}

//RESET FUNCTION
void Game::resetting()
{
	//resets all variables and clears vector
	
	buttonClickCount = 3;
	isPaused = false;
	diffNum = 3;

	stats.reset();
	bombers.clear();
	bullets.clear();
}

