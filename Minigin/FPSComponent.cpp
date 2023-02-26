#include "FPSComponent.h"

#include "TextComponent.h"
#include "GameObject.h"
#include "Time.h"

FPSComponent::FPSComponent(TextComponent* text)
	: m_pTextComponent(text)
{
}

void FPSComponent::Update(GameObject&)
{
	//If the textComponent is not set throw an error
	if (m_pTextComponent == nullptr) {
		return;
	}
	
	float elapsedTime = Time::GetInstance().GetElapsedTime();
	float FPS = 1.0f / elapsedTime;

	m_pTextComponent->SetText(std::to_string(FPS));
}

void FPSComponent::Render(const GameObject&) const
{
}

void FPSComponent::Recieve(int) const
{
}
