#pragma once
#include "Command.h"

namespace dae {

	class UpCommand final : public Command
	{
	public:
		UpCommand(GameObject* pGameObject);
		virtual void Execute() override;
	};

	class DownCommand final : public Command
	{
	public:
		DownCommand(GameObject* pGameObject);
		virtual void Execute() override;
	};

	class LeftCommand final : public Command
	{
	public:
		LeftCommand(GameObject* pGameObject);
		virtual void Execute() override;
	};

	class RightCommand final : public Command
	{
	public:
		RightCommand(GameObject* pGameObject);
		virtual void Execute() override;
	};
}

