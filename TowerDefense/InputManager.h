#pragma once
#include <SFML/Graphics.hpp>
class InputManager
{
public:
	InputManager();
	~InputManager();
	const bool is_left_mb_clicked();
	const bool is_left_mb_released();
	const bool is_right_mb_clicked();
	const bool is_right_mb_released();
	const bool is_left_mb_pressed();
	void UpdateFirst(sf::RenderWindow *rw);
	void UpdateLast();
	const sf::FloatRect GetMouseBoundingBox();
	const sf::Vector2i GetMousePosWindow();
	
	const sf::FloatRect GetMouseBoundingBoxWorld();
	const sf::Vector2f GetMousePosWorld();

private:
	bool is_leftmb_curpressed = false;
	bool is_leftmb_lastpressed = false;
	bool is_rightmb_curpressed = false;
	bool is_rightmb_lastpressed = false;
	sf::FloatRect mouseBoundingBox;
	sf::Vector2i mousePos;
	sf::Vector2f mousePosWorld;
	sf::FloatRect mouseBoundingBoxWorld;
};

