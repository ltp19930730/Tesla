#pragma once

#include "Core.h"

#include "Window.h"
#include "Tesla/Events/ApplicationEvent.h"
#include "Tesla/Events/Event.h"
#include "Tesla/LayerStack.h"

#include "Tesla/Core/Timestep.h"

#include "Tesla/ImGui/ImGuiLayer.h"


namespace Tesla {
	class TL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}

