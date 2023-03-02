#pragma once

namespace dae {

	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent(GameObject* pOwner) : m_pOwner{ pOwner } {};
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() const = 0;
		virtual void Recieve(int message) const = 0;

		GameObject* GetOwner() const { return m_pOwner; }
		void MarkForDeletion() { m_IsMarkedForDeletion = true; }
		bool IsMarkedForDeletion() { return m_IsMarkedForDeletion; }
	protected:
		GameObject* m_pOwner{};
		bool m_IsMarkedForDeletion{ false };
	};
}

