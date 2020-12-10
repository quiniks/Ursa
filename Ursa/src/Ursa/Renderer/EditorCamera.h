#pragma once
#include "glm/glm.hpp"

namespace Ursa {
	class EditorCamera {
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);
		glm::mat4 GetView() const { return m_ViewMatrix; }
		glm::mat4 GetProjection() const { return m_ProjectionMatrix; }
		glm::mat4 GetViewProjection() const { return m_ProjectionMatrix * m_ViewMatrix; }
		void SetViewportSize(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }
		void OnUpdate();
	private:
		void UpdateView();
		void UpdateProjection();
	private:
		float m_FOV = 45.0f;
		float m_AspectRatio = 1.778f;
		float m_NearClip = 0.1f;
		float m_FarClip = 1000.0f;
		float m_Pitch = 0.0f;
		float m_Yaw = 0.0f;
		float m_ViewportWidth;
		float m_ViewportHeight;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::vec3 m_Position = {0.0f, 0.0f, 3.5f};
	};
}