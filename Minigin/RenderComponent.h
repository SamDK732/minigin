#ifndef RENDERCOMPONENT
#define RENDERCOMPONENT

#include <string>
#include <memory>

#include "Component.h"
#include "Texture2D.h"

namespace dae
{
    class RenderComponent final : public Component
    {
    public:
        RenderComponent(GameObject* pGameObj);
        ~RenderComponent() override = default;

        virtual void Render() const override;

        void SetTexture(const std::string& filename);
        void SetTexture(std::shared_ptr<Texture2D> pTexture) { m_pTexture = std::move(pTexture); }

        RenderComponent(const RenderComponent& other) = delete;
        RenderComponent(RenderComponent&& other) = delete;
        RenderComponent& operator=(const RenderComponent& other) = delete;
        RenderComponent& operator=(RenderComponent&& other) = delete;

    private:
        std::shared_ptr<Texture2D> m_pTexture{};

    };
}

#endif
