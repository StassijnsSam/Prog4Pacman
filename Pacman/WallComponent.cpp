#include "WallComponent.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"

WallComponent::WallComponent(dae::GameObject* pGameObject)
	:BaseComponent(pGameObject)
{
}

void WallComponent::Initialize()
{
	//Wall has a boxCollider
	auto collider = GetOwner()->GetComponent<dae::BoxColliderComponent>();

	if (collider) {
		//Link the collision function
		collider->SetCollisionCallback([&](dae::GameObject* hit) { this->OnCollision(hit); });
	}
}

void WallComponent::Update()
{
}

void WallComponent::Render() const
{
}

void WallComponent::Recieve(int) const
{
}

void WallComponent::OnCollision(dae::GameObject*)
{
	//Wall itself does not need to do anything
}
