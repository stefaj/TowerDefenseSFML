#include "GameScreen.h"
#include <algorithm>
using namespace States;

GameScreen::GameScreen(sf::RenderWindow *rw_)
{
	this->render_window = rw_;

	gameComponents = vector<DrawableGameComponent*>();

}

void GameScreen::Update()
{
	sf::Time elapsed = clock.restart();
	float elapsed_seconds = elapsed.asSeconds();
	
	update(elapsed_seconds);
	for (int i = 0; i < gameComponents.size(); i++)
	{
		if (gameComponents[i])
		{
			if (!gameComponents[i]->ShouldDelete())
				gameComponents[i]->Update(elapsed_seconds);
		}
	}
	

}

void GameScreen::Draw()
{
	
	draw();
	for (int i = 0; i < gameComponents.size(); i++)
		gameComponents[i]->Draw(render_window);
	
}

void GameScreen::AddComponent(DrawableGameComponent *comp)
{
	if (comp)
		gameComponents.push_back(comp);
}
void GameScreen::RemoveComponent(DrawableGameComponent *comp)
{
	//gameComponents.erase()
	auto item = std::find(gameComponents.begin(), gameComponents.end(), comp);
	if (item != gameComponents.end())
		gameComponents.erase(item);

}

void GameScreen::OnLoad()
{

}

void GameScreen::ProcessEvent(sf::Event *e)
{

}


GameScreen::~GameScreen()
{
}
