#pragma once
#include <SFML/Graphics.hpp>
namespace Animation
{

	class Anim
	{
	public:
		Anim();
		~Anim();

		virtual const int GetRows()=0;
		virtual const int GetColumns() = 0;
		virtual const int FrameWidth() = 0;
		virtual const int FrameHeight() = 0;
		
		const float GetFrameTime();
		sf::Texture* GetTexture();

		const void SetFrameTime(float val);

		const bool GetIsLooping();
		void SetIsLooping(bool val);

	protected:
		bool isLooping = false;
		float frameTime;
		sf::Texture tex;
	};

}