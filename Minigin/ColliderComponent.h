#pragma once

#include <functional>
#include "BaseComponent.h"

namespace dae {
	class ColliderComponent : public BaseComponent
	{
		ColliderComponent(GameObject* pOwner);
		virtual ~ColliderComponent() = default;

		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() const override;
		virtual void Recieve(int message) const override;

		void OnCollision(ColliderComponent* other);
		void SetCollisionCallback(std::function<void(GameObject* other)> callback) { m_Callback = callback; }

	private:
		std::function<void(GameObject* other)> m_Callback{};
	};
}


