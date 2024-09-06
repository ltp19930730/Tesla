#pragma once

#include "Tesla/Scene/Scene.h"
#include "Tesla/Core/Base.h"
#include "Tesla/Core/Log.h"
#include "Tesla/Scene/Entity.h"

namespace Tesla {
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();

	private:
		void DrawEntityNode(Entity entity);


	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}