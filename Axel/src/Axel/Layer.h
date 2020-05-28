#pragma once

#include "Events/Event.h"

namespace Axel {
	class AXEL_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& event) {}

		const std::string& getName() const { return m_debugName; }
	protected:
		std::string m_debugName;
	};

}