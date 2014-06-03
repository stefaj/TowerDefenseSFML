#include "LobbyScreen.h"

using namespace States;

LobbyScreen::LobbyScreen(sf::RenderWindow *rw) : GameScreen(rw)
{
	input = new InputManager();
	//singlePlayerlbl = UI::Label(input);
	//singlePlayerlbl = UI::Label();
	refreshLbl = new UI::Label(input);
	refreshLbl->SetText("Refresh");
	refreshLbl->SetPosition(sf::Vector2f(400, 650));
	refreshLbl->On_Click.Connect(this, &LobbyScreen::Refresh);

	server = new sf::TcpListener();
	server->setBlocking(false);
	LoadContent();

	udpSock = new sf::UdpSocket();
	udpSock->setBlocking(false);

	
	updatecd = 0.0f;
}


LobbyScreen::~LobbyScreen()
{
}

void LobbyScreen::OnLoad()
{
	sf::Socket::Status status = server->listen(53000);
	isServerStarted = status == sf::Socket::Status::Done;
	if (status != sf::Socket::Done)
	{
		// error...
	}
	
	status = udpSock->bind(BROADCAST_PORT);
	if (status != sf::Socket::Status::Done)
	{
		udpSock->bind(BROADCAST_PORT+1);
	}
	
}

void LobbyScreen::LoadContent()
{
	if (!background_tex.loadFromFile("sprites/highscorebg.png"))
	{
		// error...
	}

	background_sprite.setTexture(background_tex);



	if (!font.loadFromFile("fonts/Twilight.ttf"))
	{
	}
	// Create a text
	text = sf::Text("Text", font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::White);

}
void LobbyScreen::update(float elapsed_seconds)
{
	input->UpdateFirst(render_window);
	updatecd += elapsed_seconds;

	refreshLbl->Update(elapsed_seconds);

	sf::TcpSocket *client = new TcpSocket();
	if (server->accept(*client) != sf::Socket::Done)
	{
		// error...
		delete client;
	}
	else
	{
		On_JoinGame(client,true);
	}


	///
	/// UDP BROADCAST STUFF
	///

	//Receive
	char data[100];
	std::size_t received;
	sf::IpAddress sender;
	unsigned short port = BROADCAST_PORT;
	if (udpSock->receive(data, 100, received, sender, port) == sf::Socket::Done)
	{
		if (sender == sf::IpAddress::getLocalAddress() /*&& isServerStarted*/)
		{
			//Ignore our own packets
		}
		else
		{
			if (data[0] == 'c')
			{
				if (list_of_games.find(sender) == list_of_games.end())
				{
					list_of_games[sender] = 0;
				}
				else
				{
					list_of_games[sender]++;
				}
			}
		}
		//std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
	}
	
	//Send
	if (updatecd > SECONDS_PER_BROADCAST && isServerStarted)
	{
		updatecd = 0;

		sf::IpAddress recipient = sf::IpAddress::Broadcast;

		char send_data[] = { 'c' };
		
		if (udpSock->send(send_data, 1, recipient, BROADCAST_PORT) == sf::Socket::Done)
		{
			//broadcast successful
		}
		if (udpSock->send(send_data, 1, recipient, BROADCAST_PORT+1) == sf::Socket::Done)
		{
			//broadcast successful
		}

	}

	

	int i=0;
	for (std::map<sf::IpAddress, int>::iterator iter = list_of_games.begin(); iter != list_of_games.end(); ++iter)
	{
		if (++i > 7)
			break;
		sf::IpAddress k = iter->first;
		int v = iter->second;
		
		if (text.getGlobalBounds().intersects(input->GetMouseBoundingBoxWorld()) && input->is_left_mb_clicked())
		{
			OnGameClick(k);
		}
	}
	input->UpdateLast();
}

void LobbyScreen::draw()
{
	render_window->draw(background_sprite);

	//draw ips
	int x = 400;
	int y = 170;

	int i = 0;
	for (std::map<sf::IpAddress, int>::iterator iter = list_of_games.begin(); iter != list_of_games.end(); ++iter)
	{
		if (++i > 7)
			break;
		sf::IpAddress k = iter->first;
		int v = iter->second;
	

		text.setString(k.toString());

		text.setPosition(sf::Vector2f(x + 2, y + 2));
		text.setColor(sf::Color(0, 0, 50));
		render_window->draw(text);

		text.setPosition(sf::Vector2f(x, y));
		if (text.getGlobalBounds().intersects(input->GetMouseBoundingBoxWorld()))
		{
			text.setColor(sf::Color::Yellow);
		}
		else
		{
			text.setColor(sf::Color::White);
		}
	
		
		render_window->draw(text);
		y += 64;

		
	}

	//ipLabel->Draw(render_window);
	refreshLbl->Draw(render_window);


}

void LobbyScreen::Refresh(UI::Component *c)
{
	list_of_games.clear();
}

void LobbyScreen::OnGameClick(sf::IpAddress address)
{
	TcpSocket *sock = new TcpSocket();
	sock->setBlocking(true);
	sf::Socket::Status status = sock->connect(address, 53000);
	if (status == sf::Socket::Status::Done)
	{
		On_JoinGame(sock, false);
	}

}