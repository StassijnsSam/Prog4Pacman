#pragma once

#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include <string>
#include <memory>
#include <SDL_ttf.h>

namespace dae {

	class RenderComponent;

	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(GameObject* pOwner, const std::string& text, std::shared_ptr<dae::Font> font, SDL_Color color = { 255, 255, 255 });
		TextComponent(GameObject* pOwner);
		virtual ~TextComponent() = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() const override;
		virtual void Recieve(int message) const override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);
		void SetFont(std::shared_ptr<Font> font);

	private:
		bool m_NeedsUpdate{ true };
		std::string m_Text{};
		std::shared_ptr<Font> m_pFont{};
		//default color white
		SDL_Color m_Color{ 255, 255, 255 };

		std::shared_ptr <RenderComponent> m_pRenderComponent{nullptr};
	};
}

