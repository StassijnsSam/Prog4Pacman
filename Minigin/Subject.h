#pragma once

#include "Singleton.h"
#include <vector>
#include <memory>

namespace dae {

	class GameObject;
	class Observer;

	class Subject
	{
	public:
		Subject() = default;
		virtual ~Subject() = default;

		virtual void AddObserver(Observer* pObserver);
		virtual void RemoveObserver(Observer* pObserver);
		virtual void Notify(GameObject* actor, int event);

	private:
		std::vector<Observer*> m_pObservers;
	};
}


