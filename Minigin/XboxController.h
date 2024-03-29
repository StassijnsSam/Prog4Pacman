#pragma once
#include <memory>

namespace dae {

	class XBoxController final
	{
		class XBoxControllerImpl;
		std::unique_ptr<XBoxControllerImpl> pImpl;

	public:
		enum class ControllerButton {
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000
		};

		explicit XBoxController(int controllerIndex);
		~XBoxController();
		void Update();

		bool IsDownThisFrame(ControllerButton button);
		bool IsUpThisFrame(ControllerButton button);
		bool IsPressed(ControllerButton button);

		int GetControllerIndex();
	private:
	};
}


