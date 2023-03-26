#pragma once

namespace dae {
	class GameObject;

	class Command
	{
	public:
		Command(GameObject* pGameObject);
		virtual ~Command() = default;

		virtual void Execute() = 0;

	private:
		GameObject* m_pGameObject{};
	};
}

