#include "MainMenuScreen.h"
using namespace States;

MainMenuScreen::MainMenuScreen(sf::RenderWindow *rt) : GameScreen(rt)
{
	LoadContent();
	

	input = new InputManager();
	//singlePlayerlbl = UI::Label(input);
	//singlePlayerlbl = UI::Label();
	singlePlayerlbl = new UI::Label(input);
	singlePlayerlbl->SetText("Single Player");
	singlePlayerlbl->SetPosition(sf::Vector2f(970, 316));
	singlePlayerlbl->On_Click.Connect(this, &MainMenuScreen::singlePlayer_click);

	exitlbl = new UI::Label(input);
	exitlbl->SetText("Exit");
	exitlbl->SetPosition(sf::Vector2f(970, 316+64*5));
	exitlbl->On_Click.Connect(this, &MainMenuScreen::exit_click);

	titleLabel = new UI::Label();
	titleLabel->SetCharacterSize(60);
	titleLabel->SetPosition(10, 10);
	titleLabel->SetText("Tower Defence!");
}


MainMenuScreen::~MainMenuScreen()
{
}

void MainMenuScreen::update(float elapsed_seconds)
{
	input->UpdateFirst(render_window);

	singlePlayerlbl->Update(elapsed_seconds);
	exitlbl->Update(elapsed_seconds);

	input->UpdateLast();
}

void MainMenuScreen::draw()
{
	
	render_window->draw(background_sprite);

	titleLabel->Draw(render_window);

	singlePlayerlbl->Draw(render_window);
	exitlbl->Draw(render_window);
	
}

void MainMenuScreen::LoadContent()
{
	if (!background_tex.loadFromFile("sprites/background_test2.png"))
	{
		// error...
	}

	background_sprite.setTexture(background_tex);

	if (!backgroundMusic.openFromFile("sound/201-hodomoe-drawbridge.ogg"))
	{
		//some error
	}
	backgroundMusic.setVolume(25);
	backgroundMusic.play();
	backgroundMusic.setLoop(true);
}

void MainMenuScreen::singlePlayer_hover(UI::Component *c)
{

}

void MainMenuScreen::singlePlayer_click(UI::Component *c)
{
	On_SinglePlayer(0);
	backgroundMusic.stop();
}

void MainMenuScreen::exit_click(UI::Component *c)
{
	On_Exit(0);
}