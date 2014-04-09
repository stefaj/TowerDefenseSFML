#include "PlayerObject.h"


PlayerObject::PlayerObject()
{
	owner_id = 1;
}


PlayerObject::PlayerObject(int player_id)
{
	owner_id = player_id;
}


PlayerObject::~PlayerObject()
{
}

const int PlayerObject::GetOwnerID()
{
	return owner_id;
}
