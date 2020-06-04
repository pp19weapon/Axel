#pragma once
#include "axpch.h"

#include "Core.h"
#include "Events/Event.h"


namespace Axel {
	struct WindowProps {
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps (const std::string& p_title = "Axel Engine", unsigned int p_width = 1280, unsigned int p_height = 720)
			: title(p_title),
			width(p_width),
			height(p_height)
		{}
	};


	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		// Window attributes
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual void* getNativeWindow() const = 0;

		static Window* create(const WindowProps& props = WindowProps());
	};

}