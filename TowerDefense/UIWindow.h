#pragma once
#include "Component.h"

namespace UI
{

	class UIWindow
	{
	public:
		UIWindow();
		~UIWindow();

		explicit UIWindow(sf::RenderTarget *rt);
		void Update();
		void Draw();
		void AddComponent(Component *comp);
		void RemoveComponent(Component *comp);

	protected:
		vector<Component*> ui_components;
		virtual void update(float elapsed_seconds) = 0;
		virtual void draw() = 0;
		sf::RenderTarget *render_target;
		virtual void LoadContent() = 0;
		sf::Clock clock;

	};

}