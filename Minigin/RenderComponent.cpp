#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

#include <iostream>

dae::RenderComponent::RenderComponent(GameObject* pGameObj):
    Component(pGameObj),
    m_pTexture{nullptr}
{
}
void dae::RenderComponent::Render() const
{
    if (m_pTexture)
    {
        auto& worldPos{ GetGameObj()->GetTransform().GetPosition() };
        Renderer::GetInstance().RenderTexture(*m_pTexture, worldPos.x, worldPos.y);
    }
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
    m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}