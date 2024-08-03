#pragma once

#include "Tesla/Core/Base.h"
#include "Tesla/Core/Window.h"
#include "Tesla/Events/ApplicationEvent.h"
#include "Tesla/Events/Event.h"
#include "Tesla/Core/LayerStack.h"
#include "Tesla/Core/Timestep.h"
#include "Tesla/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Tesla {
	class Application
	{
	public:
		Application(const std::string& name = "Hazel App");
		virtual ~Application();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void Close();

		Window& GetWindow() { return *m_Window; }
		static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}

