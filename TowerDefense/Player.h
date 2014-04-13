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
	const int GetLives();

	void AddGold(int amount);
	void RemoveGold(int amount);

	void AddLives(int amount);
	void RemoveLives(int amount);

private:
	int id;
	int gold;
	int creeps_killed;
	int lives;
};

