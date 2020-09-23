#pragma once

#include "Ursa.h"

class SandBox2D : public Ursa::Layer {
public:
	SandBox2D();
	virtual ~SandBox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Ursa::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Ursa::Event& e) override;
private:
	Ursa::OrthographicCameraController m_CameraController;

	//Temporary
	Ursa::Ref<Ursa::VertexArray> m_SquareVertexArray;
	Ursa::Ref<Ursa::Shader> m_FlatColorShader;
	Ursa::Ref<Ursa::Texture2D> m_CheckerTexture;
	Ursa::Ref<Ursa::Texture2D> m_TileSheet;
	Ursa::Ref<Ursa::Texture2D> m_UrsaTitle;
	std::unordered_map<char, Ursa::Ref<Ursa::SubTexture2D>> m_TextureMap;
	uint32_t m_MapWidth = 0, m_MapHeight = 0;
};