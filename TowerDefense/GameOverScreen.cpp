#include "GameOverScreen.h"
#include <iostream>
#include <string>
#include<sstream>
#include "highscorefile.h"

GameOverScreen::GameOverScreen(sf::RenderWindow *rt) : GameScreen(rt)
{
	


	input = new InputManager();

	LoadContent();
}


GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::LoadContent()
{
	closeLabel = new UI::Label(input);
	closeLabel->SetText("Done");
	closeLabel->SetPosition(sf::Vector2f(824, 382));
	closeLabel->On_Click.Connect(this, &GameOverScreen::close_click);

	descripLabel = new UI::Label(input);	
	descripLabel->SetPosition(sf::Vector2f(350, 245));

	textLabel = new UI::Label(input);
	textLabel->SetPosition(350, 340);

	if (!background_tex.loadFromFile("sprites/highscoreenter.png"))
	{
		// error...
	}

	background_sprite.setTexture(background_tex);

}

void GameOverScreen::update(float elapsed_seconds)
{
	input->UpdateFirst(render_window);

	closeLabel->Update(elapsed_seconds);

	input->UpdateLast();
}

void GameOverScreen::draw()
{
	render_window->draw(background_sprite);

	descripLabel->Draw(render_window);

	closeLabel->Draw(render_window);
	textLabel->Draw(render_window);

}


void GameOverScreen::SetScore(int s)
{
	score = s;

	std::ostringstream StrP2;
	StrP2 << "You scored: "  <<  s;
	std::string txt(StrP2.str());
	descripLabel->SetText(txt);
}


void GameOverScreen::ProcessEvent(sf::Event *e)
{
	std::string str;
	
	// In event loop...
	if (e->type == sf::Event::TextEntered)
	{
		// Handle ASCII characters only
		if (e->text.unicode < 128)
		{
			str += static_cast<char>(e->text.unicode);
			text += str;
			textLabel->SetText(text);
		}
	}

}

void GameOverScreen::close_click(UI::Component *c)
{
	HighScoreFile hsFile = HighScoreFile("highscores.txt");
	hsFile.WriteHighscore(text, score);
	On_Close(0);
}