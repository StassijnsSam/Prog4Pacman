#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::GameObject(glm::vec2 position)
{
	AddComponent<Transform>(position);
	m_pTransform = GetComponent<Transform>();
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

void dae::GameObject::FixedUpdate()
{
	for (auto& it : m_pComponents) {
		if (it.second != nullptr) {
			it.second->FixedUpdate();
		}
	}
}

void dae::GameObject::LateUpdate()
{
	
	/*for (auto& it : m_pComponents) {
		if (it.second.get() != nullptr) {
			if (it.second.get()->IsMarkedForDeletion()) {

			}
		}
	}*/
}

void dae::GameObject::Render() const
{
	for (auto& it : m_pComponents) {
		if (it.second != nullptr) {
			it.second->Render();
		}
	}
}

dae::Transform* dae::GameObject::GetTransform()
{
	return m_pTransform;
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

	//Mark all the children for deletion
	for (auto& pChild : m_pChildren) {
		if (pChild != nullptr) {
			pChild->MarkForDeletion();
		}
	}
}

void dae::GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{
	if (m_pParent == nullptr) {
		if (m_pTransform) {
			m_pTransform->SetLocalPosition(m_pTransform->GetWorldPosition());
		}
	}
	else {
		if (keepWorldPosition) {
			auto parentTransform = pParent->GetTransform();
			if (m_pTransform && parentTransform) {
				m_pTransform->SetLocalPosition(m_pTransform->GetLocaPosition() - parentTransform->GetWorldPosition());
			}
		}
		if (m_pTransform) {
			m_pTransform->SetDirty();
		}
	}
	
	//Remove from previous parent (if it exists)
	if (m_pParent != nullptr) {
		m_pParent->RemoveChild(this);
	}

	//Update parent
	m_pParent = pParent;

	//If parent is set add this as a child
	if (m_pParent != nullptr) {
		m_pParent->AddChild(this);
	}
}

const dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

void dae::GameObject::RemoveParent()
{
	SetParent(nullptr, true);
}

const std::vector<dae::GameObject*>& dae::GameObject::GetChildren()
{
	return m_pChildren;
}

void dae::GameObject::RemoveChild(GameObject* pChild)
{
	auto it = std::find(m_pChildren.begin(), m_pChildren.end(), pChild);

	if (it == m_pChildren.end()) {
		//Child was not found in the list
		return;
	}

	m_pChildren.erase(it);
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.push_back(pChild);
}

