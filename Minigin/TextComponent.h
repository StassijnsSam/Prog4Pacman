#pragma once

#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include <string>
#include <memory>

class GameObject;
class Transform;

class TextComponent final : public BaseComponent
{
public:
	TextComponent(const std::string& text, std::shared_ptr<dae::Font> font, Transform* pTransform);
	virtual ~TextComponent() = default;

	TextComponent(const TextComponent& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

	virtual void Update(GameObject& gameObject) override;
	virtual void Render(GameObject& gameObject) const override;

	void SetText(const std::string& text);

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<dae::Font> m_pFont;
	std::shared_ptr<dae::Texture2D> m_pTextTexture;

	Transform* m_pTransform;
};

