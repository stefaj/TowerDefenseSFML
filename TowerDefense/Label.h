#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "InputManager.h"
using namespace sf;
namespace UI
{
	class Label :
		public Component
	{
	public:
		Label();
		Label(InputManager *inp);
		~Label();

		void Draw(sf::RenderTarget *rw);
		const bool IsSelected();
		const bool IsSelectable();
		void Select();
		void Deselect();
		bool IsActive();
		void Activate();
		void Deactivate();
		void DoEvents(float elapsed_seconds);
		sf::FloatRect GetBoundingBox();
		void SetPosition(Vector2f pos);
		void SetPosition(float x, float y);
		void SetText(sf::String s);
		void SetColor(sf::Color col);
		void SetCharacterSize(int v);
		const sf::String GetText();

	private:
		Font font;
		Text text;
		sf::Vector2f position;
	};
}
