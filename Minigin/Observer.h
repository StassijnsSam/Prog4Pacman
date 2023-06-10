#pragma once

namespace dae {
	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const GameObject* actor, int eventID) = 0;
	};
}


