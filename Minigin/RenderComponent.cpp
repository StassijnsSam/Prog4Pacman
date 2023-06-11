#include "RenderComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"
#include "GameObject.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

dae::RenderComponent::RenderComponent(GameObject* pOwner, const std::string& filename)
	:BaseComponent(pOwner), m_TexturePath(filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::Initialize()
{
	if (m_pOwner == nullptr){
		//owner is not set correctly
		return;
	}

	auto transform = m_pOwner->GetTransform();
	if (transform == nullptr) {
		//transform component not found
		return;
	}

	m_pTransform = transform;
}

void dae::RenderComponent::Update()
{
	//Empty
	//	Got rid of formal parameter (name of gameObject)
}

void dae::RenderComponent::Render() const
{
	//Check if it is visible
	if (!m_IsVisible) {
		return;
	}
	
	if (m_pTexture == nullptr) {
		//Throw error that texture is not set
		return;
	}

	if (m_pTransform == nullptr) {
		//Throw error that transform is not set
		return;
	}

	const auto& pos = m_pTransform->GetWorldPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

void dae::RenderComponent::Recieve(int) const
{
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
	m_TexturePath = filename;
}

void dae::RenderComponent::SetTexture(std::shared_ptr<dae::Texture2D> pTexture)
{
	m_pTexture = pTexture;
}

void dae::RenderComponent::SetIsVisible(bool isVisible)
{
	m_IsVisible = isVisible;
}

const std::string& dae::RenderComponent::GetTexturePath()
{
	return m_TexturePath;
}
