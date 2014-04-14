#pragma once
#include "Anim.h"
#include "SFML\Graphics.hpp"
namespace Animation
{

	class CharacterAnim :
		public Anim
	{
	public:
		CharacterAnim();
		~CharacterAnim();

		//Settors
		void SetParameters(int w, int h);
		void LoadTexture(sf::String fileName, int row_index);

		//Accessors
		const int GetRows();
		const int GetColumns();
		const int FrameWidth();
		const int FrameHeight();

	private:
		int frameWidth = 32;
		int frameHeight = 48;
		const int rows = 1;
		const int columns = 4;
		
	};
}