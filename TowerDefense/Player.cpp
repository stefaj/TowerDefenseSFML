#include "Player.h"


Player::Player()
{
}

Player::Player(int id_)
{
	gold = 0;
	id = id_;
	lives = 10;
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