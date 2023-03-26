#include "XboxController.h"
#include <windows.h>
#include <Xinput.h>

class dae::XBoxController::XBoxControllerImpl {
public:
	XBoxControllerImpl(int controllerIndex)
		: m_ControllerIndex{ controllerIndex }
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

	}

	void Update() {
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsDownThisFrame(unsigned int button)
	{
		return m_ButtonsPressedThisFrame & button;
	}

	bool IsUpThisFrame(unsigned int button)
	{
		return m_ButtonsReleasedThisFrame & button;
	}

	bool IsPressed(unsigned int button)
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}
private:
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	int m_ControllerIndex{};
};

dae::XBoxController::XBoxController(int controllerIndex)
{
	pImpl = std::make_unique<XBoxControllerImpl>(controllerIndex);
}

dae::XBoxController::~XBoxController()
{
}

void dae::XBoxController::Update()
{
	pImpl->Update();
}

bool dae::XBoxController::IsDownThisFrame(ControllerButton button)
{
	return pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool dae::XBoxController::IsUpThisFrame(ControllerButton button)
{
	return pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool dae::XBoxController::IsPressed(ControllerButton button)
{
	return pImpl->IsPressed(static_cast<unsigned int>(button));
}
