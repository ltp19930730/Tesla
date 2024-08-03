#include <tlpch.h>
#include <Tesla.h>
#include <Tesla/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Tesla {
	class TeslaEditor : public Application
	{
	public:
		TeslaEditor()
			: Application("TESLA editor")
		{
			PushLayer(new EditorLayer());
		}

		~TeslaEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new TeslaEditor();
	}
}