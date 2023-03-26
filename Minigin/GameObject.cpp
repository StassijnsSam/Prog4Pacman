#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject()
{
	//Clear the components vector and children vector
	m_pComponents.clear();
	m_pChildren.clear();
}

void dae::GameObject::Initialize()
{
	for (auto& it : m_pComponents) {
		if (it.second != nullptr) {
			it.second->Initialize();
		}
	}
}

void dae::GameObject::Update()
{
	for (auto& it : m_pComponents) {
		if (it.second != nullptr) {
			it.second->Update();
		}
	}
}

void dae::GameObject::LateUpdate()
{
	for (auto& it : m_pComponents) {
		if (it.second != nullptr && it.second->IsMarkedForDeletion()) {
			it.second.reset();
			//it.second = nullptr;
		}
	}
}

void dae::GameObject::Render() const
{
	for (auto& it : m_pComponents) {
		if (it.second != nullptr) {
			it.second->Render();
		}
	}
}

void dae::GameObject::Send(int message)
{
	//Send message to all components
	for (auto& it : m_pComponents) {
		if (it.second != nullptr) {
			it.second->Recieve(message);
		}
	}
}

void dae::GameObject::MarkForDeletion()
{
	m_IsMarkedForDeletion = true;

	//Also mark all of the components of this object for deletion
	for (const auto& it : m_pComponents) {
		if (it.second != nullptr) {
			it.second->MarkForDeletion();
		}
	}
}

dae::GameObject* dae::GameObject::GetParent()
{
	return m_pParent;
}

const std::vector<std::unique_ptr<dae::GameObject>>& dae::GameObject::GetChildren()
{
	return m_pChildren;
}

void dae::GameObject::AddChild(std::unique_ptr<GameObject> pChild, bool keepWorldPosition)
{
	auto transform = GetComponent<Transform>();
	auto pParent = pChild.get()->GetParent();

	if (pParent == nullptr) {
		if (transform) {
			transform->SetLocalPosition(transform->GetWorldPosition());
		}
	}
	else {
		if (keepWorldPosition) {
			auto parentTransform = pParent->GetComponent<Transform>();
			if (transform && parentTransform) {
				transform->SetLocalPosition(transform->GetLocaPosition() - parentTransform->GetWorldPosition());
			}
		}
		if (transform) {
			transform->SetDirty();
		}
	}

	//Remove from previous parent (if it exists)
	if (pParent != nullptr) {
		pParent->RemoveChildFromList(std::move(pChild));
	}

	//Update parent
	pChild.get()->SetParent(this);

	//If parent is set add this as a child
	AddChildToList(std::move(pChild));

}

void dae::GameObject::RemoveChild(std::unique_ptr<GameObject> pChild)
{
	RemoveChildFromList(std::move(pChild));
}

void dae::GameObject::SetParent(GameObject* pParent)
{
	m_pParent = pParent;
}

void dae::GameObject::RemoveChildFromList(std::unique_ptr<GameObject> pChild)
{
	auto it = std::find(m_pChildren.begin(), m_pChildren.end(), pChild);

	if (it == m_pChildren.end()) {
		//Child was not found in the list
		return;
	}

	m_pChildren.erase(it);
}

void dae::GameObject::AddChildToList(std::unique_ptr<GameObject>&& pChild)
{
	m_pChildren.push_back(pChild);
}

