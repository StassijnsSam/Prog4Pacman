#pragma once
#include "BaseComponent.h"

class TextComponent;

class FPSComponent final : public BaseComponent
{
public:

	FPSComponent(TextComponent* text);
	virtual ~FPSComponent() = default;

	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) = delete;

	virtual void Update(GameObject& gameObject) override;
	virtual void Render(const GameObject& gameObject) const override;
	virtual void Recieve(int message)const override;

private:

	TextComponent* m_pTextComponent;
};

