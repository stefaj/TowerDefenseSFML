#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
using namespace sf;
namespace UI
{
	class Label :
		public Component
	{
	public:
		Label();
		~Label();

		void Draw(sf::RenderTarget *rw);
		const bool IsSelected();
		const bool IsSelectable();
		void Select();
		void Deselect();
		bool IsActive();
		void Activate();
		void Deactivate();
		void DoEvents(sf::RenderTarget *rw, float elapsed_seconds);
		sf::FloatRect GetBoundingBox();
		void SetPosition(Vector2f pos);
		void SetText(sf::String s);


	private:
		Font font;
		Text text;
	};
}
