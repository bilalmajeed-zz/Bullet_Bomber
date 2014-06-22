#include "StatUpdate.h"

//constructor
StatUpdate::StatUpdate():
	m_score(0), //initialize the score at 0
	m_kills(0), //kills at 0
	m_health(100) //and health at 100
{
	//try to load the font, and return error if it cant
	if (!m_font.loadFromFile("scoreFont.TTF"))
		cout << "Could not load Font file" << endl;
}

//update the score
void StatUpdate::scoreUpdate(string type, int increase)
{
	//if the score update is a kill then add the increase indicated
	//otherwise just add one to the score

	if (type == "kills")
		m_score += increase;
	else
		m_score++;
}
	
void StatUpdate::killsUpdate()
{
	//increment the kills counter
	m_kills++;
}

void StatUpdate::healthUpdate(int change)
{
	//take the indicated health away from the health counter
	m_health -= change;
}

void StatUpdate::draw(sf::RenderWindow & window)
{
	// CONVERT INT TO STRING for all the texts
	string strScore;
	string strKills;
	string strHealth;
	ostringstream scoreConvert;
	ostringstream killsConvert;
	ostringstream healthConvert;

	scoreConvert << m_score;
	strScore = scoreConvert.str();

	killsConvert << m_kills;
	strKills = killsConvert.str();

	healthConvert << m_health;
	strHealth = healthConvert.str();

	// SETUP TEXT
	sf::Text score(strScore, m_font, 41);
	score.setColor(sf::Color(255, 255, 255));
	score.setPosition(260, 651);

	sf::Text kills(strKills, m_font, 21);
	kills.setColor(sf::Color(255, 255, 255));
	kills.setPosition(155, 704);

	sf::Text health(strHealth, m_font, 21);
	health.setColor(sf::Color(246, 98, 98));
	health.setPosition(300, 704);

	// DRAW TEXT
	window.draw(score);
	window.draw(kills);
	window.draw(health);
}

int StatUpdate::getScore()
{
	return m_score;
}

int StatUpdate::getKills()
{
	return m_kills;
}

int StatUpdate::getHealth()
{
	return m_health;
}

void StatUpdate::reset()
{
	//RESET THE SCORE, KILLS, AND HEALTH of the player ship
	m_score = 0;
	m_health = 100;
	m_kills = 0;
}