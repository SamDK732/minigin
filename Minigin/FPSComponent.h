#ifndef FPSCOMPONENT
#define FPSCOMPONENT

#include "Component.h"

#include <iostream>

namespace dae
{
    class GameObject;
    class TextComponent;

    class FPSComponent final : public Component
    {
    public:
        FPSComponent(GameObject* pGameObj);
        ~FPSComponent() override = default;

        virtual void Update() override;

        FPSComponent(const FPSComponent& other) = delete;
        FPSComponent(FPSComponent&& other) = delete;
        FPSComponent& operator=(const FPSComponent& other) = delete;
        FPSComponent& operator=(FPSComponent&& other) = delete;

    private:
        unsigned m_FrameCount;
        float m_AccumulatedTime;

        TextComponent* m_pTextComp;
    };
}

#endif