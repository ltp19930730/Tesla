#pragma once

#include "Tesla/Core/Layer.h"
#include "Tesla/Events/KeyEvent.h"
#include "Tesla/Events/MouseEvent.h"
#include "Tesla/Events/ApplicationEvent.h"

namespace Tesla {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();
		void BlockEvents(bool block) { m_BlockEvents = block; }
		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}

