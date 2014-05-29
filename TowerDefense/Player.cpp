#include "Player.h"


Player::Player()
{
}

Player::Player(int id_, bool isHost)
{
	gold = 0;
	id = id_;
	lives = 10;
	host = isHost;
}


Player::~Player()
{
}


const int Player::GetGold()
{
	return gold;
}

const int Player::GetID()
{
	return id;
}

const int Player::GetCreepsKilled()
{
	return creeps_killed;
}

const int Player::GetLives()
{
	return lives;
}

void Player::AddGold(int amount)
{
	gold += amount;
}

void Player::RemoveGold(int amount)
{
	gold -= amount;
}

void Player::AddLives(int amount)
{
	lives += amount;
}

void Player::RemoveLives(int amount)
{
	lives -= amount;
}

const bool Player::IsHost()
{
	return host;
}

void Player::AddCreepsKilled(int amount)
{
	creeps_killed += amount;
}

void Player::RemoveCreepsKilled(int amount)
{
	creeps_killed -= amount;
}

void Player::SetGold(int val)
{
	gold = val;
}
void Player::SetLives(int val)
{
	lives = val;
}
void Player::SetCreepsKilled(int val)
{
	creeps_killed = val;
}