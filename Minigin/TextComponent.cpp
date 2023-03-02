#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "RenderComponent.h"
#include "GameObject.h"



dae::TextComponent::TextComponent(GameObject* pOwner, const std::string& text, std::shared_ptr<dae::Font> font, SDL_Color color)
	:BaseComponent(pOwner), m_pFont{font}, m_Color{color}, m_Text{text}
{
}

dae::TextComponent::TextComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void dae::TextComponent::Initialize()
{
	if (m_pOwner == nullptr) {
		//owner not set correctly
		return;
	}

	auto renderComponent = m_pOwner->GetComponent<RenderComponent>();
	if (renderComponent == nullptr) {
		//rendercomponent not found
		return;
	}

	m_pRenderComponent = renderComponent;
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		//const SDL_Color color = { 255,255,255 }; 
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		auto pTexture = std::make_shared<dae::Texture2D>(texture);

		if (m_pRenderComponent != nullptr) {
			m_pRenderComponent->SetTexture(pTexture);
		}
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
}

void dae::TextComponent::Recieve(int) const
{
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
}

void dae::TextComponent::SetFont(std::shared_ptr<dae::Font> font)
{
	m_pFont = font;
}
