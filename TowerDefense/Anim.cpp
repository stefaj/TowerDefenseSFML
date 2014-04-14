#include "Anim.h"
using namespace Animation;

Anim::Anim()
{
	frameTime = 0;
	isLooping = false;
}


Anim::~Anim()
{
}

const float Anim::GetFrameTime()
{
	return frameTime;
}

const void Anim::SetFrameTime(float val)
{
	frameTime = val; 
}

const bool Anim::GetIsLooping()
{
	return isLooping;
}

sf::Texture* Anim::GetTexture()
{
	return &tex;
}