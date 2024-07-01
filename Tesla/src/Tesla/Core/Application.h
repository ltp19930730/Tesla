#pragma once

#include "Tesla/Core/Core.h"
#include "Tesla/Core/Window.h"
#include "Tesla/Events/ApplicationEvent.h"
#include "Tesla/Events/Event.h"
#include "Tesla/Core/LayerStack.h"
#include "Tesla/Core/Timestep.h"
#include "Tesla/ImGui/ImGuiLayer.h"


namespace Tesla {
	class Application
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
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}

