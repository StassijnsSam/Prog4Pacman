#pragma once
#include "Command.h"

namespace dae {

	class UpCommand final : public Command
	{
		UpCommand(GameObject* pGameObject);
		virtual void Execute() override;
	};

	class DownCommand final : public Command
	{
		DownCommand(GameObject* pGameObject);
		virtual void Execute() override;
	};

	class LeftCommand final : public Command
	{
		LeftCommand(GameObject* pGameObject);
		virtual void Execute() override;
	};

	class RightCommand final : public Command
	{
		RightCommand(GameObject* pGameObject);
		virtual void Execute() override;
	};
}

