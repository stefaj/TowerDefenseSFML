#pragma once
#include "Anim.h";
#include <SFML/Graphics.hpp>
#include "DrawableGameComponent.h"

namespace Animation
{
	class AnimPlayer : public States::DrawableGameComponent
	{
	public:
		AnimPlayer();
		~AnimPlayer();

		//General
		void Reset(Anim*);
		void PlayAnimation(Anim*);
		void Update(float elapsed_seconds);
		void Draw(sf::RenderTarget*);

		//Getters
		Anim* GetAnimation();
		const int GetFrameIndex();
		const sf::Vector2f GetOrigin();
		const sf::Vector2f GetPosition();
		const sf::FloatRect GetGlobalBounds();

		//Setters
		void SetAnimation(Anim*);
		void SetPosition(sf::Vector2f);
		void SetFrameIndex(int v);
		void SetScale(float s);

	private:
		Anim *animation;
		int frameIndex;
		float time;
		sf::Sprite sprite;


	};

}