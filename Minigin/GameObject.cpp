#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

void dae::GameObject::Update()
{
	for (auto &p : m_pComponents)
	{
		p->Update();
	}
}

void dae::GameObject::Render() const
{
	for (const auto& p : m_pComponents)
	{
		p->Render();
	}
}
