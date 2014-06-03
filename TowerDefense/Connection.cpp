#include "connection.h"

const sf::Int32 magic_num = 9;

using namespace Networking;
Connection::Connection()
{
}

Connection::Connection(sf::TcpSocket *s)
{
	this->sock = s;
	sock->setBlocking(false);
	
}

void Connection::Send(TowerStruct h)
{
	sf::Packet packet;

	sf::Int32 packet_type = PACKETTYPES::NewTower;

	packet << magic_num << packet_type << h.owner_ << h.type_ << h.x << h.y;

	std::cout << magic_num << packet_type << h.owner_ << h.type_ << h.x << h.y;

	sf::Socket::Status status = sock->send(packet);

}

void Connection::Send(ProjectileStruct p)
{
	sf::Packet packet;

	sf::Int32 packet_type = PACKETTYPES::NewProjectile;

	packet << magic_num << packet_type << p.damage << p.end_x << p.end_y << p.owner_ << p.start_x << p.start_y << p.towerLevel;

	std::cout << magic_num << packet_type << p.damage << p.end_x << p.end_y << p.owner_ << p.start_x << p.start_y << p.towerLevel;

	sf::Socket::Status status = sock->send(packet);
}

void Connection::Send(EnemyStruct p)
{
	sf::Packet packet;

	sf::Int32 packet_type = PACKETTYPES::NewEnemy;

	packet << magic_num << packet_type << p.owner_ << p.type_ << p.x << p.y;

	std::cout << magic_num << packet_type << p.owner_ << p.type_ << p.x << p.y << p.UID;

	sf::Socket::Status status = sock->send(packet);
}

void Connection::Send(RemoveEnemyStruct es)
{
	sf::Packet packet;

	sf::Int32 packet_type = PACKETTYPES::RemoveEnemy;

	packet << magic_num << packet_type << es.uid;

	std::cout << magic_num << packet_type << es.uid;

	sf::Socket::Status status = sock->send(packet);
}

void Connection::Send(PlayerSyncStruct s)
{
	sf::Packet packet;

	sf::Int32 packet_type = PACKETTYPES::PlayerSync;

	packet << magic_num << packet_type << s.p1_lives << s.p2_lives << s.p1_kills << s.p2_kills << s.p1_gold << s.p2_gold << s.p1_passiveGold << s.p2_passiveGold;

	//std::cout << magic_num << packet_type << s.p1_lives << s.p2_lives << s.p1_kills << s.p2_kills << s.p1_gold << s.p2_gold << s.p1_passiveGold << s.p2_passiveGold;

	sf::Socket::Status status = sock->send(packet);
}

void Connection::Send(UpdateEnemyStruct en)
{
	sf::Packet packet;

	sf::Int32 packet_type = PACKETTYPES::UpdateEnemy;

	packet << magic_num << packet_type << en.health << en.UID << en.x << en.y;

	std::cout << magic_num << packet_type << en.health << en.UID << en.x << en.y;

	sf::Socket::Status status = sock->send(packet);
}

void Connection::Update(float elapsed_time)
{
	// Receive the packet at the other end
	sf::Packet packet;
	sf::Socket::Status status = sock->receive(packet);	
	if (status == sf::Socket::Status::NotReady)
		return;
	sf::Int32 magic;
	while (packet >> magic)
	{
	
		if (magic == magic_num)
		{
			sf::Int32 packet_type;
			packet >> packet_type;

			if (packet_type == PACKETTYPES::NewTower)
			{
				TowerStruct tower;
				packet >> tower.owner_ >> tower.type_ >> tower.x >> tower.y;
				OnNewTowerReceived(tower);
			}

			if (packet_type == PACKETTYPES::RemoveEnemy)
			{
				RemoveEnemyStruct en;
				packet >> en.uid;
				OnRemoveEnemyReceived(en);
			}

			if (packet_type == PACKETTYPES::NewEnemy)
			{
				EnemyStruct en;
				packet >> en.owner_ >> en.type_ >> en.x >> en.y >> en.UID;
				OnNewEnemyReceived(en);

			}

			if (packet_type == PACKETTYPES::UpdateEnemy)
			{
				UpdateEnemyStruct en;
				packet >> en.health >> en.UID >> en.x >> en.y;
				OnUpdateEnemyReceived(en);
			}

			if (packet_type == PACKETTYPES::PlayerSync)
			{
				PlayerSyncStruct s;

				packet >> s.p1_lives >> s.p2_lives >> s.p1_kills >> s.p2_kills >> s.p1_gold >> s.p2_gold >> s.p1_passiveGold >> s.p2_passiveGold;
				
				OnNewPSyncRecieved(s);
			}


			if (packet_type == PACKETTYPES::NewProjectile)
			{

				ProjectileStruct p;

				packet >> p.damage >> p.end_x >> p.end_y >> p.owner_ >> p.start_x >> p.start_y >> p.towerLevel;
				OnNewProjectileRecieved(p);
			}
		}

	}

}