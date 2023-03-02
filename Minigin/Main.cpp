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
#include "Scene.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "FPSComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Add background
	auto background = std::make_shared<GameObject>();


	background.get()->AddComponent<Transform>();
	auto backgroundRenderComponent = background.get()->AddComponent<RenderComponent>();

	backgroundRenderComponent->SetTexture("background.tga");

	scene.Add(background);

	////Add logo
	//auto logo = std::make_shared<GameObject>();
	//
	//auto logoTransform = new Transform();
	//logoTransform->SetPosition(216, 180);

	//auto logoRenderComponent = new RenderComponent("logo.tga", logoTransform);

	//logo.get()->AddComponent<Transform>(logoTransform);
	//logo.get()->AddComponent<RenderComponent>(logoRenderComponent);

	//scene.Add(logo);

	////Add text
	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//auto title = std::make_shared<GameObject>();

	//auto titleTransform = new Transform();
	//titleTransform->SetPosition(80, 20);

	//auto titleRenderComponent = new RenderComponent("logo.tga", titleTransform);

	//auto titleTextComponent = new TextComponent("Programming 4 Assignment",  font, {255, 255, 255}, titleRenderComponent);

	//title.get()->AddComponent<Transform>(titleTransform);
	//title.get()->AddComponent<TextComponent>(titleTextComponent);
	//title.get()->AddComponent<RenderComponent>(titleRenderComponent);

	//scene.Add(title);

	////Add FPS counter
	//auto fontFPS = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);

	//auto FPSCounter = std::make_shared<GameObject>();

	//auto FPSTransform = new Transform();
	//FPSTransform->SetPosition(10, 10);

	//auto FPSRenderComponent = new RenderComponent("logo.tga", FPSTransform);

	////	 Text is yellow
	//auto FPSTextComponent = new TextComponent("0 FPS", fontFPS, {255, 255, 0}, FPSRenderComponent);

	//auto FPSCounterComponent = new FPSComponent(FPSTextComponent);

	//FPSCounter.get()->AddComponent<Transform>(FPSTransform);
	//FPSCounter.get()->AddComponent<TextComponent>(FPSTextComponent);
	//FPSCounter.get()->AddComponent<FPSComponent>(FPSCounterComponent);
	//FPSCounter.get()->AddComponent<RenderComponent>(FPSRenderComponent);

	//scene.Add(FPSCounter);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}