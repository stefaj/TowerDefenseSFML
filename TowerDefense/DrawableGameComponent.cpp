#include "DrawableGameComponent.h"
using namespace States;

void DrawableGameComponent::MarkForDeletion()
{
	should_delete = true;
}

const bool DrawableGameComponent::ShouldDelete()
{
	return should_delete;
}