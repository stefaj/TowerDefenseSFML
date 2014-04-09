#pragma once
class Player
{
public:
	Player();
	Player(int id_);
	~Player();

	const int GetGold();
	const int GetID();
	const int GetCreepsKilled();

	void AddGold(int amount);
	void RemoveGold(int amount);

private:
	int id;
	int gold;
	int creeps_killed;

};

