#pragma once

#include "Singleton.h"
#include "ColliderComponent.h"
#include "GameObject.h"

namespace dae {
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void Add(ColliderComponent* colliderComponent);
		void Remove(ColliderComponent* colliderComponent);

		void FixedUpdate();

	private:
		std::vector<ColliderComponent*> m_pColliders{};
	};
}


