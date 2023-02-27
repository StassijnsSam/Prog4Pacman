#pragma once

class GameObject;

class BaseComponent
{
public:
	BaseComponent() = default;
	virtual ~BaseComponent() = default;

	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	virtual void Update(GameObject& gameObject) = 0;
	virtual void Render(const GameObject& gameObject) const = 0;
	virtual void Recieve(int message) const = 0;

	GameObject* GetOwner() const { return m_pOwner; }
	void MarkForDeletion(){ m_MarkedForDeletion = true; }
	bool IsMarkedForDeletion() { return m_MarkedForDeletion; }
protected:
	GameObject* m_pOwner{};
	bool m_MarkedForDeletion{ false };
};

