#include "ScreenManager.h"

using namespace States;
ScreenManager::ScreenManager(sf::RenderWindow *rw)
{
	window = rw;
}

ScreenManager::ScreenManager()
{
}


ScreenManager::~ScreenManager()
{
}


void ScreenManager::Draw()
{


	activeScreen->Draw();

	if (activeScreen == screens["map"])
		PostMapDraw(window);

	if (in_transition && transition_time < transition_speed)
	{
		window->draw(last_trans_spr);

	}

}

void ScreenManager::Update(float elapsed_seconds)
{
	if (in_transition && transition_time < transition_speed)
	{
		transition_time += elapsed_seconds;
		last_trans_spr.move(WINDOW_WIDTH* elapsed_seconds / transition_speed, 0);
		last_trans_spr.setColor(sf::Color(255, 255, 255, 255 - 255 * transition_time / transition_speed));
	}

	activeScreen->Update();
	if (activeScreen == screens["map"])
		PostMapUpdate(window);

}

void ScreenManager::ProcessEvent(sf::Event *e)
{
	activeScreen->ProcessEvent(e);
}

const GameScreen* ScreenManager::GetScreen(std::string screenName)
{
	return screens[screenName];
}

void ScreenManager::TransitionToScreen(std::string screenName)
{
	sf::Image img = window->capture();
	last_trans_tex.loadFromImage(img);
	last_trans_spr = sf::Sprite(last_trans_tex);

	in_transition = true;
	activeScreen = screens[screenName];
	activeScreen->OnLoad();
	transition_time = 0;
}

void ScreenManager::AddScreen(std::string screenName, GameScreen *screen)
{
	screens[screenName] = screen;
}

void ScreenManager::RemoveScreen(std::string screenName)
{
	screens.erase(screenName);
}