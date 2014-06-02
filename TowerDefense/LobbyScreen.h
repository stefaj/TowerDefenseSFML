#pragma once
#include "GameScreen.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Label.h"
#include "InputManager.h"
#include "Component.h"
#include "Signalling\Signal.h";
#include "SFML/Network.hpp"
#include <vector>

namespace States
{
	class LobbyScreen : public GameScreen
	{
	public:
		LobbyScreen(sf::RenderWindow *rw);
		~LobbyScreen();

		void singlePlayer_click(UI::Component *c);
		void highscore_click(UI::Component *c);
		void multiPlayer_click(UI::Component *c);

		void exit_click(UI::Component *c);

		Gallant::Signal2<sf::TcpSocket*,bool> On_JoinGame;

		void Refresh(UI::Component *c);
		void OnGameClick(sf::IpAddress address);

		void OnLoad();
	private:
		sf::Texture background_tex;
		sf::Sprite background_sprite;
		void update(float elapsed_seconds);
		void draw();
		void LoadContent();

		//slots
		

		InputManager *input;

		UI::Label *refreshLbl;
		sf::TcpListener *server;
		bool isServerStarted;

		Font font;
		Text text;

		//Show list of active games
		sf::UdpSocket *udpSock;
		std::map<sf::IpAddress, int> list_of_games;

		float updatecd;
		const float SECONDS_PER_BROADCAST = 5.0f;
		const unsigned short BROADCAST_PORT = 54000;

	};
}
