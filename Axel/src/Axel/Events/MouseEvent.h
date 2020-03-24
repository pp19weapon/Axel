#pragma once

#include "Event.h"

#include <sstream>

namespace Axel {
	class AXEL_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y)
			: m_mouseX(x),
			m_mouseY(y) {}

		inline float getX() const { return m_mouseX; }
		inline float getY() const { return m_mouseY; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseMoved)

	private:
		float m_mouseX;
		float m_mouseY;
	};

	

	class AXEL_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_xOffset(xOffset),
			m_yOffset(yOffset) {}

		inline float getXOffset() { return m_xOffset; }
		inline float getYOffset() { return m_yOffset; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseScrollEvent: " << m_xOffset << ", " << m_yOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_xOffset, m_yOffset;
	};

	class AXEL_API MouseButtonEvent : public Event
	{
	public:
		inline int getMouseButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button)
			: m_button(button) {}

		int m_button;
	};

	class AXEL_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class AXEL_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}