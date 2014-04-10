#pragma once
#include "DrawableGameComponent.h"
#include "InputManager.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "Signalling\Signal.h";
using namespace std;
using namespace States;
namespace UI
{
	class Component : public DrawableGameComponent
	{
	public:
		Component();
		Component(InputManager *input);
		virtual void Draw(sf::RenderWindow *rw)=0;
		void Update(sf::RenderWindow *rw, float elapsed_seconds);
		virtual ~Component();
		const virtual bool IsSelected()=0;
		const virtual bool IsSelectable()=0;
		virtual void Select()=0;
		virtual void Deselect()=0;
		virtual bool IsActive()=0;
		virtual void Activate()=0;
		virtual void Deactivate()=0;
		virtual void DoEvents(sf::RenderWindow *rw, float elapsed_seconds)=0;
		virtual sf::FloatRect GetBoundingBox()=0;
		Gallant::Signal1<Component*> On_Click;
		Gallant::Signal1<Component*> On_MouseHover;
		void SetProperty(string name, string value);
		string GetProperty(string name);
	private:
		InputManager *input;
		unordered_map<string, string> properties;
	};

}