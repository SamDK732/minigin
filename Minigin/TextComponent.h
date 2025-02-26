#ifndef TEXTCOMPONENT
#define TEXTCOMPONENT

#include "Component.h"
#include "GameObject.h"
#include <memory>
#include <string>

namespace dae
{
    class Font;
    class Texture2D;
    class RenderComponent;

    class TextComponent final :
        public Component
    {
    public:
        TextComponent(GameObject* pGameObj, std::shared_ptr<Font> font);
        ~TextComponent() override = default;

        virtual void Update() override;

        void SetText(const std::string& text);

        TextComponent(const TextComponent& other) = delete;
        TextComponent(TextComponent&& other) = delete;
        TextComponent& operator=(const TextComponent& other) = delete;
        TextComponent& operator=(TextComponent&& other) = delete;

    private:
        bool m_NeedsUpdate;
        std::string m_Text;

        std::shared_ptr<Font> m_pFont;
        RenderComponent* m_pRenderComponent;
    };
}

#endif
