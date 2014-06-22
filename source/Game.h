//MAIN GAME CLASS
//every thing gets called and intialized here

#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


#include "Menu.h" //main menu class
#include "OptionsMenu.h" //options menu class
#include "InstructionsMenu.h" //instructions menu class
#include "GameOverMenu.h" //game over menu class
#include "SplashScreen.h" //splash screen class
#include "Background.h" //background class
#include "PlayerShip.h" //player class
#include "EnemyShip.h" //enemy class
#include "EnemyManager.h" //enemy manager class
#include "BulletManager.h" //bullet manager class
#include "StatUpdate.h" // stats update class

//files for the time and fps
#include <cstdlib>
#include <ctime>
#include <sstream>

class Game
{
public:
	void start(); //starts the game
	
	//CONSTANTS
	const static int SCREEN_WIDTH = 500;
	const static int SCREEN_HEIGHT = 750;

	const static int SCREEN_LEFT_POS = 50;
	const static int SCREEN_BOTTOM_POS = 648;
	const static int SCREEN_TOP_POS = 0;
	const static int SCREEN_RIGHT_POS = 449;

private:
	static bool isExiting(); //check if the game is ending
	static void GameLoop(); //the game loop

	static void showMenu(); //shows the menu
	static void showSplashScreen(); //shows the splash screen
	static void showOptions(); //shows the options screen
	static void showInstructions(); //shows the instructions screen
	static void showGameOverScreen(); //shows the game over screen
	static void resetting(); //resettign the game

	//makes an enum of all the different states that game could be in
	enum GameState
	{
		Uninitialized,
		ShowingSplashScreen,
		ShowingMainMenu,
		ShowingOptions,
		Paused,
		Playing,
		Leaving,
		ShowingInstructions,
		GameOver,
		Exiting
	};
	
	//data members
	static int diffNum;
	static bool isPaused; 
	static bool isSoundOn;
	static int buttonClickCount;
	static sf::Clock clock;
	
	//for music
	static sf::Music menuMusic;
	static sf::Music bgMusic;
	static sf::Sound bulletSound;
	sf::SoundBuffer bulletBuffer;

	//ALL THE VISIBLE GAME OBJECTS
	static BulletManager bullets; //bullets object

	static PlayerShip player; //player object
	static EnemyManager bombers; // enemies object

	static StatUpdate stats; //score, health, kills manager object

	//background image
	static Background bg_bottom; 
	static Background bg_top;
	
	static GameState gameState;
	static sf::RenderWindow mainWindow;
	
	static VisibleGameObject cursor; //hitbox object 
	static VisibleGameObject soundOffButton; //sound off button object

	static VisibleGameObject pause; //pause screen object
	static VisibleGameObject leavingScreen; //leaving screen object
	static VisibleGameObject optionsScreen; //options screen object
	static VisibleGameObject instructionsScreen; //instructions screen object
	static VisibleGameObject gameOverScreen; //game over screen
	static VisibleGameObject redScreen60; //red screen for blood effect
	static VisibleGameObject redScreen30; //red screen for blood effect
};
