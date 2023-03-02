#pragma once
#include <memory>
#include "Transform.h"
#include <unordered_map>
#include <typeindex>

class BaseComponent;

namespace dae {
	class GameObject final {
	public:
		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Initialize();
		void Update();
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
			auto component = std::make_shared<ComponentType>(this, std::forward<Args>(args)...);

			m_pComponents.emplace(typeIndex, component);

			return component.get();
		};

		template <typename ComponentType> ComponentType* GetComponent() const {
			//Check if it has a component of this type
			if (!HasComponent<ComponentType>()) {
				//Some kind of error or logging
				return nullptr;
			}

			const std::type_index typeIndex = std::type_index(typeid(ComponentType));

			ComponentType* component = dynamic_cast<ComponentType*>(m_pComponents.at(typeIndex).get());

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

		void Send(int message);

		bool IsMarkedForDeletion() { return m_IsMarkedForDeletion; }
		void MarkForDeletion();

	private:
		//ID system for gameObjects?
		bool m_IsMarkedForDeletion{ false };
		std::unordered_map<std::type_index, std::shared_ptr<BaseComponent>> m_pComponents{};
	};
}
