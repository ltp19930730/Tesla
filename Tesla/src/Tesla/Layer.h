#pragma once

#include "tlpch.h"
#include "Tesla/Core.h"
#include "Tesla/Core/Timestep.h"
#include "Tesla/Events/Event.h"

namespace Tesla {
	class TL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {};

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;

	};
}