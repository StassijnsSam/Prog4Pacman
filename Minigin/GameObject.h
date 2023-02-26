#pragma once
#include <memory>
#include "Transform.h"

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

		//template <typename T> T* AddComponent();
		//template <typename T> T* GetComponent() const;
		//template <typename T> void RemoveComponent();

	private:
		Transform m_transform{};
	};
}
