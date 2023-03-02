#pragma once

#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include <string>
#include <memory>
#include <SDL_ttf.h>

class RenderComponent;

class TextComponent final : public BaseComponent
{
public:
	//TextComponent(const std::string& text, std::shared_ptr<dae::Font> font, SDL_Color color, RenderComponent* pRenderComponent);
	TextComponent(GameObject* pOwner);
	virtual ~TextComponent() = default;

	TextComponent(const TextComponent& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

	virtual void Update(GameObject& gameObject) override;
	virtual void Render(const GameObject& gameObject) const override;
	virtual void Recieve(int message) const override;

	void SetText(const std::string& text);

private:
	bool m_NeedsUpdate{ false };
	std::string m_Text{};
	std::shared_ptr<dae::Font> m_pFont{};
	SDL_Color m_Color{};

	RenderComponent* m_pRenderComponent{};
};

