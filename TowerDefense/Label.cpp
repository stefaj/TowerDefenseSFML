#include "Label.h"


using namespace UI;



Label::Label()
{
	
	if (!font.loadFromFile("fonts/Twilight.ttf"))
	{
		//Error
		int a = 1;
		a = a;
	}
	// Create a text
	text = sf::Text("Text", font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::White);

}


Label::~Label()
{
}

void Label::SetText(sf::String s)
{
	text.setString(s);
}

void Label::SetPosition(Vector2f pos)
{
	text.setPosition(pos);
}

void Label::Draw(sf::RenderWindow *rw)
{
	rw->draw(text);
}

const bool Label::IsSelected()
{
	return false;
}

const bool Label::IsSelectable()
{
	return false;
}

void Label::Select()
{

}

void Label::Deselect()
{

}

bool Label::IsActive()
{
	return false;
}

void Label::Activate()
{

}

void Label::Deactivate()
{

}

void Label::DoEvents(sf::RenderWindow *rw, float elapsed_seconds)
{

}

sf::FloatRect Label::GetBoundingBox()
{
	return text.getGlobalBounds();
}