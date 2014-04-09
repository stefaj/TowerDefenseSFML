#include "Player.h"


Player::Player()
{
}

Player::Player(int id_)
{
	gold = 0;
	id = id_;
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

void Player::AddGold(int amount)
{
	gold += amount;
}

void Player::RemoveGold(int amount)
{
	gold -= amount;
}
