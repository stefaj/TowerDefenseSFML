#pragma once
class Player
{
public:
	Player();
	Player(int id_, bool isHost);
	~Player();

	const int GetGold();
	const int GetID();
	const int GetCreepsKilled();
	const int GetLives();
	const bool IsHost();

	void AddGold(int amount);
	void RemoveGold(int amount);

	void AddLives(int amount);
	void RemoveLives(int amount);

	void AddCreepsKilled(int amount);
	void RemoveCreepsKilled(int amount);

	void SetGold(int val);
	void SetLives(int val);
	void SetCreepsKilled(int val);

private:
	int id;
	int gold;
	int creeps_killed;
	int lives;
	bool host;
};

