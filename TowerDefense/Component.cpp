#include "Component.h"
using namespace UI;

Component::Component()
{
}

Component::Component(InputManager *ip)
{
	input = ip;
}

Component::~Component()
{
}

void Component::Update(sf::RenderTarget *rw, float elapsed_seconds)
{
	if (GetBoundingBox().intersects(input->GetMouseBoundingBox()))
	{
		On_MouseHover(this);
		if (input->is_left_mb_released())
			On_Click(this);
	}
	DoEvents(rw,elapsed_seconds);
}

void Component::SetProperty(string name, string value)
{
	properties.insert({ name, value });
}

string Component::GetProperty(string name)
{
	return properties.at(name);
}