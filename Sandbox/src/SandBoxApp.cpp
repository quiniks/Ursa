#include <Ursa.h>
#include "Ursa/Core/EntryPoint.h"

#pragma warning(push)
#pragma warning(disable : 6011)
#pragma warning(disable : 26495)
#include "imgui/imgui.h"
#pragma warning(pop)
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SandBox2D.h"

/*
class ExampleLayer : public Ursa::Layer {
public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.0f/720.0f, true) {
		//Triangle/////////////
		m_TriVertexArray = Ursa::VertexArray::Create();

		float triVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,		1.0f, 0.4f, 0.7f, 1.0f,
			0.5f, -0.5f, 0.0f,		0.9f, 0.9f, 0.6f, 1.0f,
			0.0f, 0.5f, 0.0f,		0.4f, 0.8f, 0.8f, 1.0f
		};

		Ursa::Ref<Ursa::VertexBuffer> triVertexBuffer;
		triVertexBuffer.reset(Ursa::VertexBuffer::Create(triVertices, sizeof(triVertices)));
		triVertexBuffer->SetLayout({
			{ Ursa::ShaderDataType::Float3, "a_Position" },
			{ Ursa::ShaderDataType::Float4, "a_Color" }
			});
		m_TriVertexArray->AddVertexBuffer(triVertexBuffer);

		uint32_t triIndices[3] = { 0, 1, 2 };
		Ursa::Ref<Ursa::IndexBuffer> triIndexBuffer;
		triIndexBuffer.reset(Ursa::IndexBuffer::Create(triIndices, sizeof(triIndices) / sizeof(uint32_t)));
		m_TriVertexArray->SetIndexBuffer(triIndexBuffer);

		//Square/////////////
		m_SquareVertexArray = Ursa::VertexArray::Create();

		float sqrVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ursa::Ref<Ursa::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Ursa::VertexBuffer::Create(sqrVertices, sizeof(sqrVertices)));
		squareVertexBuffer->SetLayout({
			{ Ursa::ShaderDataType::Float3, "a_Position" },
			{ Ursa::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t sqrIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ursa::Ref<Ursa::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Ursa::IndexBuffer::Create(sqrIndices, sizeof(sqrIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);


		m_Shader = Ursa::Shader::Create("assets/shaders/VertexColorShader.glsl");
		m_FlatColorShader = Ursa::Shader::Create("assets/shaders/FlatColorShader.glsl");
		auto textureShader =  m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Ursa::Texture2D::Create("assets/textures/Checkerboard.png");
		m_FireTexture = Ursa::Texture2D::Create("assets/textures/burn.png");

		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);
	}

	void OnUpdate(Ursa::TimeStep timeStep) override {
		m_CameraController.OnUpdate(timeStep);

		Ursa::RenderCommand::SetClearColor({ 0.8f, 0.2f, 0.3f, 1.0f });
		Ursa::RenderCommand::Clear();

		Ursa::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_FlatColorShader->Bind();
		m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Ursa::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Ursa::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_FireTexture->Bind();
		Ursa::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


		// Triangle
		Ursa::Renderer::Submit(m_Shader, m_TriVertexArray);

		Ursa::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Ursa::Event& event) override {
		m_CameraController.OnEvent(event);
	}
private:
	Ursa::ShaderLibrary m_ShaderLibrary;
	Ursa::Ref<Ursa::Shader> m_Shader;
	Ursa::Ref<Ursa::Shader> m_FlatColorShader;
	//Ursa::Ref<Ursa::Shader> m_TextureShader;
	Ursa::Ref<Ursa::VertexArray> m_TriVertexArray;
	Ursa::Ref<Ursa::VertexArray> m_SquareVertexArray;
	Ursa::Ref<Ursa::Texture2D> m_Texture;
	Ursa::Ref<Ursa::Texture2D> m_FireTexture;

	Ursa::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.4f, 0.8f, 0.8f };
};
*/

class Sandbox : public Ursa::Application {
public:
	Sandbox() {
		//PushLayer(new ExampleLayer());
		PushLayer(new SandBox2D());
	}

	~Sandbox() {

	}
};

Ursa::Application* Ursa::CreateApplication() {
	return new Sandbox();
}