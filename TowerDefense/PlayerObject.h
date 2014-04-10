#pragma once
class PlayerObject
{
public:
	PlayerObject();
	explicit PlayerObject(int player_id);
	~PlayerObject();
	const int GetOwnerID();
private:
	int owner_id;
};

