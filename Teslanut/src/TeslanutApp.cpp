#include <tlpch.h>
#include <Tesla.h>
#include <Tesla/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Tesla {
	class Teslanut : public Application
	{
	public:
		Teslanut()
			: Application("Teslanut")
		{
			PushLayer(new EditorLayer());
		}

		~Teslanut()
		{

		}
	};

	Application* CreateApplication()
	{
		return new Teslanut();
	}
}