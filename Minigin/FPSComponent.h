#pragma once
#include "BaseComponent.h"
#include <memory>

namespace dae {

	class TextComponent;

	class FPSComponent final : public BaseComponent
	{
	public:

		FPSComponent(GameObject* pOwner);
		virtual ~FPSComponent() = default;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() const override;
		virtual void Recieve(int message)const override;

	private:
		const float m_MinTime{ 1.0f };
		float m_CurrTime{ 0.0f };
		int m_FrameAmount{ 0 };

		TextComponent* m_pTextComponent{};
	};
}

