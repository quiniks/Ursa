#include "ursapch.h"
#include "EditorCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Ursa {
	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip) 
		: m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip)
	{
		UpdateView();
		UpdateProjection();
	}

	void EditorCamera::OnUpdate()
	{
		UpdateView();
		UpdateProjection();
		m_Pitch = m_Pitch + 0.001f;
	}

	void EditorCamera::UpdateView()
	{
		float cosPitch = cos(m_Pitch);
		float sinPitch = sin(m_Pitch);
		float cosYaw = cos(m_Yaw);
		float sinYaw = sin(m_Yaw);

		glm::vec3 right =	{ cosYaw, 0, -sinYaw };								
		glm::vec3 up =		{ sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
		glm::vec3 forward = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

		m_ViewMatrix[0][0] = -right.x;
		m_ViewMatrix[1][0] = -right.y;
		m_ViewMatrix[2][0] = -right.z;

		m_ViewMatrix[0][1] = -up.x;
		m_ViewMatrix[1][1] = -up.y;
		m_ViewMatrix[2][1] = -up.z;

		m_ViewMatrix[0][2] = forward.x;
		m_ViewMatrix[1][2] = forward.y;
		m_ViewMatrix[2][2] = forward.z;

		m_ViewMatrix[3][0] = glm::dot(right, m_Position);
		m_ViewMatrix[3][1] = glm::dot(up, m_Position);
		m_ViewMatrix[3][2] = -glm::dot(forward, m_Position);

		m_ViewMatrix[0][3] = 0;
		m_ViewMatrix[1][3] = 0;
		m_ViewMatrix[2][3] = 0;
		m_ViewMatrix[3][3] = 1;
	}

	void EditorCamera::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_ProjectionMatrix = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
	}
}
