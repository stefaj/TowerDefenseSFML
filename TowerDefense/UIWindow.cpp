#include "UIWindow.h"

using namespace UI;

UIWindow::UIWindow(sf::RenderTarget *rw_)
{
	this->render_target = rw_;

	ui_components = vector<Component*>();

}

void UIWindow::Update()
{
	sf::Time elapsed = clock.restart();
	float elapsed_seconds = elapsed.asSeconds();

	update(elapsed_seconds);
	for (int i = 0; i < ui_components.size(); i++)
		ui_components[i]->Update(render_target, elapsed_seconds);


}

void UIWindow::Draw()
{

	draw();
	for (int i = 0; i < ui_components.size(); i++)
		ui_components[i]->Draw(render_target);

}

void UIWindow::AddComponent(Component *comp)
{
	if (comp)
		ui_components.push_back(comp);
}
void UIWindow::RemoveComponent(Component *comp)
{
	//gameComponents.erase()
	auto item = std::find(ui_components.begin(), ui_components.end(), comp);
	if (item != ui_components.end())
		ui_components.erase(item);

}


UIWindow::~UIWindow()
{
}
