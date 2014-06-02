#include "HighscoreScreen.h"
#include <iostream>
#include <string>
#include<sstream>

using namespace States;

HighscoreScreen::HighscoreScreen(sf::RenderWindow *rt) : GameScreen(rt)
{
	LoadContent();


	input = new InputManager();
	//singlePlayerlbl = UI::Label(input);
	//singlePlayerlbl = UI::Label();

	nameLabel = new UI::Label(input);
	
	


	backLabel = new UI::Label(input);
	backLabel->SetText("Back");
	backLabel->On_Click.Connect(this, &HighscoreScreen::back_click);
	backLabel->SetPosition(sf::Vector2f(970, 316 + 64 * 5));
}


HighscoreScreen::~HighscoreScreen()
{
}

void HighscoreScreen::update(float elapsed_seconds)
{
	input->UpdateFirst(render_window);

	backLabel->Update(elapsed_seconds);

	input->UpdateLast();
}

void HighscoreScreen::draw()
{
	render_window->draw(background_sprite);

	backLabel->Draw(render_window);

	int x = 400;
	int y = 170;
	for (int i = 0; i < scores.size(); i++)
	{
		if (i>6)
			break;

		Highscore s = scores[i];
		std::ostringstream StrP2;
		StrP2 << s.user << ": " << s.score;
		std::string txt(StrP2.str());
		nameLabel->SetText(txt);

		nameLabel->SetPosition(x, y);
		y += 64;

		nameLabel->Draw(render_window);

	}

}

void HighscoreScreen::LoadContent()
{
	if (!background_tex.loadFromFile("sprites/highscorebg.png"))
	{
		// error...
	}

	background_sprite.setTexture(background_tex);

}


void HighscoreScreen::OnLoad()
{
	HighScoreFile hsFile = HighScoreFile("highscores.txt");
	scores = hsFile.GetScores();
}

void HighscoreScreen::back_click(UI::Component *c)
{
	On_Close(0);
}