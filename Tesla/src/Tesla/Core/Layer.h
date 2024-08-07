#pragma once

#include "tlpch.h"
#include "Tesla/Core/Base.h"
#include "Tesla/Core/Timestep.h"
#include "Tesla/Events/Event.h"

namespace Tesla {
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts, float time) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {};

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;

	};
}