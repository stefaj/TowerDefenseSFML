#include "InputManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}


void InputManager::UpdateFirst(sf::RenderWindow *rw)
{
	is_leftmb_curpressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	is_rightmb_curpressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
	
	mousePos = sf::Mouse::getPosition(*rw);
	mousePosWorld = rw->mapPixelToCoords(mousePos);
	
	mouseBoundingBox = sf::FloatRect(mousePos.x, mousePos.y, 8, 8);
	mouseBoundingBoxWorld = sf::FloatRect(mousePosWorld.x, mousePosWorld.y, 8, 8);
}

void InputManager::UpdateLast()
{
	is_leftmb_lastpressed = is_leftmb_curpressed;
	is_rightmb_lastpressed = is_rightmb_curpressed;
}


const bool InputManager::is_left_mb_clicked()
{
	return (is_leftmb_curpressed && !is_leftmb_lastpressed);
}

const bool InputManager::is_left_mb_released()
{
	return is_leftmb_lastpressed && !is_leftmb_curpressed;
}

const bool InputManager::is_right_mb_clicked() 
{
	return is_rightmb_curpressed && !is_rightmb_lastpressed;
}

const bool InputManager::is_right_mb_released()
{
	return is_rightmb_lastpressed && !is_rightmb_curpressed;
}

const sf::FloatRect InputManager::GetMouseBoundingBox()
{
	return mouseBoundingBox;
}
const sf::FloatRect InputManager::GetMouseBoundingBoxWorld()
{
	return mouseBoundingBoxWorld;
}

const sf::Vector2i InputManager::GetMousePosWindow()
{
	return mousePos;
}

const sf::Vector2f InputManager::GetMousePosWorld()
{
	return mousePosWorld;
}

const bool InputManager::is_left_mb_pressed()
{
	return is_leftmb_curpressed;
}