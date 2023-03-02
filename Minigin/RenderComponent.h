#pragma once
#include <memory>
#include <string>
#include "Texture2D.h"
#include "BaseComponent.h"

namespace dae {

	//class Texture2D;
	class Transform;

	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(GameObject* pOwner);
		RenderComponent(GameObject* pOwner, const std::string& filename);
		virtual ~RenderComponent() = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() const override;
		virtual void Recieve(int message) const override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<dae::Texture2D> pTexture);
	private:

		std::shared_ptr<dae::Texture2D> m_pTexture{ nullptr };
		Transform* m_pTransform{ nullptr };
	};
}

