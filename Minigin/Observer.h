#pragma once

namespace dae {
	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const GameObject* actor, int eventID) = 0;
	};
}


