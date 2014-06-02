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

Label::Label(InputManager *inp) : Component(inp)
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
	//text.setPosition(pos);
	position = pos;
}

void Label::SetPosition(float x, float y)
{
	//text.setPosition(pos);
	position = Vector2f(x, y);
}

void Label::Draw(sf::RenderTarget *rw)
{
	sf::View prevView = rw->getView();
	sf::FloatRect viewPort = prevView.getViewport();
	sf::Vector2f size = prevView.getSize();
	sf::Vector2f center = prevView.getCenter();
	float rotation = prevView.getRotation();
	float left = center.x - size.x / 2;
	float top = center.y - size.y / 2;

	//t1_sprite.setPosition(left + 128, top + size.y - 128 + 64 + 1);
	
	text.setPosition(sf::Vector2f(left + position.x+2, top + position.y+2));
	text.setColor(sf::Color(0, 0, 50));
	rw->draw(text);


	text.setPosition(sf::Vector2f(left + position.x, top + position.y));

	if (hover && input)
	{
		text.setColor(sf::Color::Yellow);
	}
	else
	{
		text.setColor(sf::Color::White);
	}

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

void Label::DoEvents(float elapsed_seconds)
{

}

sf::FloatRect Label::GetBoundingBox()
{
	return text.getGlobalBounds();
}

void Label::SetColor(sf::Color col)
{
	text.setColor(col);
	
}

void Label::SetCharacterSize(int v)
{
	text.setCharacterSize(v);
}

const sf::String Label::GetText()
{
	return text.getString();
}