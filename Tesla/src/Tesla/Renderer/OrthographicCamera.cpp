#include "tlpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Tesla {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top),
		  m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
							  glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateProjectionMatrix()
	{
		m_ProjectionMatrix = glm::ortho(m_Left, m_Right, m_Bottom, m_Top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::ZoomIn(float amount)
	{
		// Ensure that we don't zoom in too much
		float minZoom = 0.1f; // Minimum allowed size for the projection parameters
		float aspectRatio = 16.0f / 9.0f;
		float newWidth = (m_Right - m_Left) - 2 * amount;
		float newHeight = (m_Top - m_Bottom) - 2 * amount / aspectRatio;

		if (newWidth > minZoom && newHeight > minZoom / aspectRatio) {
			m_Left += amount;
			m_Right -= amount;
			m_Bottom += amount / aspectRatio;
			m_Top -= amount / aspectRatio;
			RecalculateProjectionMatrix();
		}
	}

	void OrthographicCamera::ZoomOut(float amount)
	{
		float aspectRatio = 16.0f / 9.0f;
		m_Left -= amount;
		m_Right += amount;
		m_Bottom -= amount / aspectRatio;
		m_Top += amount / aspectRatio;
		RecalculateProjectionMatrix();
	}
}