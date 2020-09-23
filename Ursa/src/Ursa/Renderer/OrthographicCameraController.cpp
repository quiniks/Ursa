#include "ursapch.h"
#include "OrthographicCameraController.h"
#include "Ursa/Core/Input.h"
#include "Ursa/Core/KeyCodes.h"

namespace Ursa {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(TimeStep timeStep)
	{
		URSA_PROFILE_FUNCTION();
		if (Input::IsKeyPressed(URSA_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * timeStep;
		else if (Input::IsKeyPressed(URSA_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * timeStep;
		if (Input::IsKeyPressed(URSA_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * timeStep;
		else if (Input::IsKeyPressed(URSA_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * timeStep;

		if (m_Rotation) {
			if (Input::IsKeyPressed(URSA_KEY_E))
				m_CameraRotation += m_CameraRotationSpeed * timeStep;
			if (Input::IsKeyPressed(URSA_KEY_Q))
				m_CameraRotation -= m_CameraRotationSpeed * timeStep;
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		URSA_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(URSA_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(URSA_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));

	}

	void OrthographicCameraController::CalculateView()
	{
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		URSA_PROFILE_FUNCTION();
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_ZoomLevel = std::min(m_ZoomLevel, 25.0f);
		CalculateView();
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		URSA_PROFILE_FUNCTION();
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		CalculateView();
		return false;
	}
}