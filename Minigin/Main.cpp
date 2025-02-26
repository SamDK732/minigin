#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto backGround{ std::make_shared<dae::GameObject>() };
	auto textureComp{ std::make_unique<dae::RenderComponent>(backGround.get()) };
	textureComp->SetTexture("background.tga");
	backGround->AddComponent(std::move(textureComp));
	scene.Add(backGround);

	auto logo{ std::make_shared<dae::GameObject>() };
	auto textureCompLogo{ std::make_unique<dae::RenderComponent>(logo.get()) };
	textureCompLogo->SetTexture("logo.tga");
	logo->AddComponent(std::move(textureCompLogo));
	logo->GetTransform().SetPosition(216, 180, 0);
	scene.Add(logo);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text{ std::make_shared<dae::GameObject>() };
	auto textureCompTxt{ std::make_unique<dae::RenderComponent>(text.get()) }; //Needs to be added before next creation
	text->AddComponent(std::move(textureCompTxt));
	auto textComp{ std::make_unique<dae::TextComponent>(text.get(), font) };
	textComp->SetText("Programming 4 Assignment");
	text->AddComponent(std::move(textComp));
	text->GetTransform().SetPosition(80, 20, 0);
	scene.Add(text);

	auto fps{ std::make_shared<dae::GameObject>() };
	auto fpsTextureComp{ std::make_unique<dae::RenderComponent>(fps.get()) };
	fps->AddComponent(std::move(fpsTextureComp));
	auto fpsTextComp{ std::make_unique<dae::TextComponent>(fps.get(), font) };
	fpsTextComp->SetText("0");
	fps->AddComponent(std::move(fpsTextComp)); //Needs to be added before next creation
	auto fpsComp{ std::make_unique<dae::FPSComponent>(fps.get()) };
	fps->AddComponent(std::move(fpsComp));
	scene.Add(fps);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}