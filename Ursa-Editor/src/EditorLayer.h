#pragma once

#include "Ursa.h"

namespace Ursa {
	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(TimeStep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		Ursa::OrthographicCameraController m_CameraController;

		//Temporary
		Ref<VertexArray> m_SquareVertexArray;
		Ref<Shader> m_FlatColorShader;
		Ref<FrameBuffer> m_FrameBuffer;
		Ref<Texture2D> m_CheckerTexture;
		Ref<Texture2D> m_TileSheet;
		Ref<Texture2D> m_UrsaTitle;
		std::unordered_map<char, Ref<SubTexture2D>> m_TextureMap;
		uint32_t m_MapWidth = 0, m_MapHeight = 0;
	};
}