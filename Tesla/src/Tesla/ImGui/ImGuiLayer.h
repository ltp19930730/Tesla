#pragma once

#include "Tesla/Core/Layer.h"
#include "Tesla/Events/KeyEvent.h"
#include "Tesla/Events/MouseEvent.h"
#include "Tesla/Events/ApplicationEvent.h"

namespace Tesla {
	class TL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}

