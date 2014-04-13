#pragma once
#include <SFML/Graphics.hpp>

namespace States
{	class DrawableGameComponent
	{
	public:
		virtual void Update(sf::RenderTarget* window, float elapsed_seconds) = 0;
		virtual void Draw(sf::RenderTarget* window) = 0;
		void MarkForDeletion();
		const bool ShouldDelete();
	private:
		bool should_delete = false;
	};

}