#pragma once
#include <memory>
#include "Transform.h"
#include <unordered_map>
#include <typeindex>
#include "Transform.h"

class BaseComponent;

namespace dae {
	class GameObject final {
	public:
		GameObject(glm::vec2 position = glm::vec2{});
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Initialize();
		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render() const;

		template <typename ComponentType, typename... Args> ComponentType* AddComponent(Args&&... args) {
			//Check if it already has a component of this type
			if (HasComponent<ComponentType>()) {
				//2 options
				//	Throw an error
				//	Delete the old component and add the new one (need to LOG!)
				return nullptr;
			}

			const std::type_index typeIndex = std::type_index(typeid(ComponentType));
			//Make a new component of this type and instantly set the owner
			auto component = std::make_unique<ComponentType>(this, std::forward<Args>(args)...);

			m_pComponents.emplace(typeIndex, std::move(component));

			return dynamic_cast<ComponentType*>(m_pComponents.at(typeIndex).get());
		};

		template <typename ComponentType> ComponentType* GetComponent() const {
			//Check if it has a component of this type
			if (!HasComponent<ComponentType>()) {
				//Some kind of error or logging
				return nullptr;
			}

			const std::type_index typeIndex = std::type_index(typeid(ComponentType));

			auto component = dynamic_cast<ComponentType*>(m_pComponents.at(typeIndex).get());

			return component;
		};

		template <typename ComponentType> bool RemoveComponent() {
			//Check if it has a component of this type
			if (!HasComponent<ComponentType>()) {
				return false;
			}

			const std::type_index typeIndex = std::type_index(typeid(ComponentType));

			//Mark the component for deletion
			ComponentType* component = m_pComponents.at(typeIndex);
			component->MarkForDeletion();

			//Erase from container
			m_pComponents.erase(typeIndex);

			return true;
		};

		template <typename ComponentType> bool HasComponent() const {
			const std::type_index typeIndex = std::type_index(typeid(ComponentType));

			return m_pComponents.contains(typeIndex);
		}

		Transform* GetTransform();

		//Messages
		void Send(int message);

		//Deletion
		bool IsMarkedForDeletion() { return m_IsMarkedForDeletion; }
		void MarkForDeletion();

		//Children
		void SetParent(GameObject* pParent, bool keepWorldPosition);
		const GameObject* GetParent() const;
		void RemoveParent();
		const std::vector<GameObject*>& GetChildren();

	private:
		bool m_IsMarkedForDeletion{ false };

		//Components
		std::unordered_map<std::type_index, std::unique_ptr<BaseComponent>> m_pComponents{};
		Transform* m_pTransform{};

		//Parent and children
		void RemoveChild(GameObject* pChild);
		void AddChild(GameObject* pChild);
		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren{};
	};
}
