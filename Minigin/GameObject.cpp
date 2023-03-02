#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

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

