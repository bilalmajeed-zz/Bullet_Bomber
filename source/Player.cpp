#include "Player.h"
#include <assert.h>
#include "Game.h"

Player::Player()
{
	load("images//ship.png");
	assert(isLoadedAccess());
	getSprite().setOrigin(16,16);
}

Player::~Player()
{
}

void Player::draw(sf::RenderWindow & window)
{
	VisibleGameObject::draw(window);
}

void Player::update()
{
}
