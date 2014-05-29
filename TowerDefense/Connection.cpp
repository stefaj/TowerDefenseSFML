#include "connection.h"

const sf::Int32 magic_num = 9;

using namespace Networking;
Connection::Connection()
{
}

Connection::Connection(sf::TcpSocket *s)
{
	this->sock = s;
	sock->setBlocking(true);
	
}

void Connection::Send(TowerStruct h)
{
	
	//ck->waitForConnected();
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

	std::cout << magic_num << packet_type << p.owner_ << p.type_ << p.x << p.y;

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

	packet << magic_num << packet_type << s.p1_lives << s.p2_lives << s.p1_kills << s.p2_kills << s.p1_gold << s.p2_gold;

	std::cout << magic_num << packet_type << s.p1_lives << s.p2_lives << s.p1_kills << s.p2_kills << s.p1_gold << s.p2_gold;

	sf::Socket::Status status = sock->send(packet);
}


void Connection::Update(float elapsed_time)
{
	// Receive the packet at the other end
	sf::Packet packet;
	sf::Socket::Status status = sock->receive(packet);	

	sf::Int32 magic;
	if (packet >> magic && magic == magic_num)
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
			packet >> en.owner_ >> en.type_ >> en.x >> en.y;
			OnNewEnemyReceived(en);

		}

		if (packet_type == PACKETTYPES::PlayerSync)
		{
			PlayerSyncStruct s;

			packet >> s.p1_lives >> s.p2_lives >> s.p1_kills >> s.p2_kills >> s.p1_gold >> s.p2_gold;
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