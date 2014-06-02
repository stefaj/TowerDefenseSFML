#include "WinnerScreen.h"

using namespace States;

WinnerScreen::WinnerScreen(sf::RenderWindow *rt) : GameScreen(rt)
{
	LoadContent();


	input = new InputManager();
	//singlePlayerlbl = UI::Label(input);
	//singlePlayerlbl = UI::Label();


	backLabel = new UI::Label(input);
	backLabel->SetText("Back");
	backLabel->On_Click.Connect(this, &WinnerScreen::back_click);
	backLabel->SetPosition(sf::Vector2f(970, 316 + 64 * 5));

	isWinner = false;
}


WinnerScreen::~WinnerScreen()
{
}


void WinnerScreen::update(float elapsed_seconds)
{
	input->UpdateFirst(render_window);

	backLabel->Update(elapsed_seconds);

	input->UpdateLast();
}

void WinnerScreen::draw()
{
	render_window->draw(background_sprite);

	backLabel->Draw(render_window);
	
	render_window->draw(text);

}

void WinnerScreen::SetWinner(bool didWin)
{
	isWinner = didWin;
	if (isWinner)
		text.setString("Winner");
	else
		text.setString("Loser");
	text.setPosition((WINDOW_WIDTH - text.getGlobalBounds().width) / 2, (WINDOW_HEIGHT - text.getGlobalBounds().height) / 2);
}

void WinnerScreen::LoadContent()
{
	if (!background_tex.loadFromFile("sprites/dimmed_bg.png"))
	{
		// error...
	}

	background_sprite.setTexture(background_tex);


	if (!font.loadFromFile("fonts/Twilight.ttf"))
	{
	}
	// Create a text
	text = sf::Text("Text", font);
	text.setCharacterSize(128);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::White);
	text.setString("Winner");
	text.setPosition((WINDOW_WIDTH - text.getGlobalBounds().width) / 2, (WINDOW_HEIGHT - text.getGlobalBounds().height) / 2);

}


void WinnerScreen::back_click(UI::Component *c)
{
	On_Close(0);
}