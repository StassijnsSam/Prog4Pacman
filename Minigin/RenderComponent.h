#pragma once
#include <memory>
#include "BaseComponent.h"
#include <string>
#include "Texture2D.h"

//class Texture2D;
class Transform;

class RenderComponent final : public BaseComponent
{
public:
	RenderComponent();
	RenderComponent(Transform* pTransform);
	virtual ~RenderComponent() = default;

	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;

	virtual void Update(GameObject& gameObject) override;
	virtual void Render(GameObject& gameObject) const override;

	void SetTexture(const std::string& filename);
private:

	std::shared_ptr<dae::Texture2D> m_pTexture{nullptr};
	Transform* m_pTransform{ nullptr };
};

