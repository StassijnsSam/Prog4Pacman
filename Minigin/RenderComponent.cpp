#include "RenderComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"
#include "GameObject.h"

RenderComponent::RenderComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{
	//m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void RenderComponent::Update(GameObject&)
{
	//Empty
	//	Got rid of formal parameter (name of gameObject)
}

void RenderComponent::Render(const GameObject&) const
{
	if (m_pTexture == nullptr) {
		//Throw error that texture is not set
		return;
	}

	if (m_pTransform == nullptr) {
		//Throw error that transform is not set
		return;
	}

	const auto& pos = m_pTransform->GetPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

void RenderComponent::Recieve(int) const
{
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void RenderComponent::SetTexture(std::shared_ptr<dae::Texture2D> pTexture)
{
	m_pTexture = pTexture;
}
