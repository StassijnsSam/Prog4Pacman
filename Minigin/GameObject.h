#pragma once
#include <memory>
#include "Transform.h"
#include <unordered_map>
#include <typeindex>

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		
		void Update();
		void Render() const;

		template <typename ComponentType> void AddComponent(ComponentType* component) {
			//Check if it already has a component of this type
			if (HasComponent<ComponentType>()) {
				//2 options
				//	Throw an error
				//	Delete the old component and add the new one (need to LOG!)
				return;
			}
			
			const std::type_index typeIndex = std::type_index(typeid(ComponentType));

			m_pComponents.emplace(typeIndex, component);
		};

		template <typename ComponentType> ComponentType* GetComponent() const {
			//Check if it has a component of this type
			if (!HasComponent<ComponentType>()) {
				//Some kind of error or logging, otherwise nullptr issues in the future possibly
				return nullptr;
			}

			const std::type_index typeIndex = std::type_index(typeid(ComponentType));

			ComponentType* component = m_pComponents.at(typeIndex);

			return component;
		};

		template <typename ComponentType> bool RemoveComponent() {
			//Check if it has a component of this type
			if (!HasComponent<ComponentType>()) {
				return false;
			}

			const std::type_index typeIndex = std::type_index(typeid(ComponentType));

			//Delete the component
			ComponentType* component = m_pComponents.at(typeIndex);
			delete component;
			component = nullptr;

			//Erase from container
			m_pComponents.erase(typeIndex);

			return true;
		};

		template <typename ComponentType> bool HasComponent() {
			const std::type_index typeIndex = std::type_index(typeid(ComponentType));

			return m_pComponents.contains(typeIndex);
		}

		void Send(int message);

	private:
		//ID system for gameObjects?
		std::unordered_map<std::type_index, BaseComponent*> m_pComponents{};
	};
}
