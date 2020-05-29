#pragma once

#include "Axel/Input.h"

namespace Axel {
	class WindowsInput : public Input {
	protected:
		virtual bool isKeyPressedImpl(int keycode) override;
		virtual bool isKeyReleasedImpl(int keycode) override;

		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual bool isMouseButtonReleasedImpl(int button) override;

		std::pair<float, float> getMousePositionImpl() override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;


	};
}