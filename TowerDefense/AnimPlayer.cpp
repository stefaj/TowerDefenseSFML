#include "AnimPlayer.h"
using namespace Animation;

AnimPlayer::AnimPlayer()
{

}


AnimPlayer::~AnimPlayer()
{

}

void AnimPlayer::Reset(Anim *a)
{
	animation = a;
	frameIndex = 0;
	time = 0;
	
}

void AnimPlayer::PlayAnimation(Anim* a)
{
	if (a == animation)
		return;
	animation = a;
	frameIndex = 0;
	time = 0;

	sprite.setTexture(*animation->GetTexture());
	
}

void AnimPlayer::Update(float elapsed_seconds)
{
	if (!(animation))
		return;
	time += elapsed_seconds;
	while (time > animation->GetFrameTime())
	{
		time -= animation->GetFrameTime();
		if (animation->GetIsLooping())
		{
			frameIndex = (frameIndex + 1) % animation->GetColumns();
		}
	}
	const int column = 1;
	sf::IntRect rect = sf::IntRect(frameIndex * animation->FrameWidth(), animation->FrameHeight() * (column - 1), animation->FrameWidth(), animation->FrameHeight());
	
	sprite.setTextureRect(rect);
}

void AnimPlayer::Draw(sf::RenderTarget *rw)
{
	rw->draw(sprite);
}


Anim* AnimPlayer::GetAnimation()
{
	return animation;
}

const sf::Vector2f AnimPlayer::GetOrigin()
{
	return sf::Vector2f((int)(animation->FrameWidth() / 2), (int)(animation->FrameHeight() / 2));
}

const sf::Vector2f AnimPlayer::GetPosition()
{
	return sprite.getPosition();
}

const sf::FloatRect AnimPlayer::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}

void AnimPlayer::SetAnimation(Anim *an)
{
	animation = an;
}

void AnimPlayer::SetPosition(sf::Vector2f v)
{
	sprite.setPosition(v);
}

void AnimPlayer::SetFrameIndex(int v)
{
	frameIndex = v;
}

const int AnimPlayer::GetFrameIndex()
{
	return frameIndex;
}

void AnimPlayer::SetScale(float s)
{
	sprite.setScale(s, s);
}

void AnimPlayer::SetTint(const sf::Color &col)
{
	sprite.setColor(col);
}