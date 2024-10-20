#pragma once

#include "Tesla.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Tesla/Renderer/EditorCamera.h"

namespace Tesla {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts, float time) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private:

	    Ref<Texture2D> m_CheckerboardTexture;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;

		EditorCamera m_EditorCamera;

		int m_GizmoType = 0;

		SceneHierarchyPanel m_SceneHierarchyPanel;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
	};
}
