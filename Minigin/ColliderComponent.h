#pragma once

#include <functional>
#include "BaseComponent.h"

namespace dae {
	class ColliderComponent : public BaseComponent
	{
	public:
		ColliderComponent(GameObject* pOwner);
		virtual ~ColliderComponent();

		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() const override;
		virtual void Recieve(int message) const override;

		virtual void OnCollision(ColliderComponent* other);
		virtual void SetCollisionCallback(std::function<void(GameObject* other)> callback);

		//Make this an abstract class
		virtual bool IsColliding(ColliderComponent* other) = 0;

	private:
		std::function<void(GameObject* other)> m_Callback{};
	};
}


