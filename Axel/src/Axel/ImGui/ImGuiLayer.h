#pragma once

#include "Axel/Layer.h"
#include "Axel/Events/MouseEvent.h"
#include "Axel/Events/KeyEvent.h"
#include "Axel/Events/ApplicationEvent.h"


namespace Axel {
	class AXEL_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;


		void begin();
		void end();
	private:
		float m_time = 0.0f;
	};
}