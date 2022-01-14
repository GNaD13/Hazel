#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckerBoardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	//Timer timer("Sandbox2D::OnUpdate", BIND_BENCH_FN(SetProfile));
	HZ_PROFILE_FUNCTION();
	{
		HZ_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	Hazel::Renderer2D::ResetStats();
	{
		HZ_PROFILE_SCOPE("Renderer Prep");
		Hazel::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Hazel::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		HZ_PROFILE_SCOPE("Renderer Draw");
		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Hazel::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
		Hazel::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.5f, 10.5f }, m_CheckerBoardTexture, 10.0f);
		Hazel::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, rotation, { 0.9f, 0.3f, 0.5f, 1.0f });
		Hazel::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerBoardTexture, 20.0f);

		for (float x = -5.0f; x <= 5.0f; x += 0.5f)
		{
			for (float y = -5.0f; y <= 5.0f; y += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f };
				Hazel::Renderer2D::DrawQuad({ x, y }, { 0.45, 0.45 }, color);
			}
		}

		Hazel::Renderer2D::EndScene();
	}

	//std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->Bind();
	//std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void Sandbox2D::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();

	Hazel::Renderer2D::Statistic stats = Hazel::Renderer2D::GetStats();

	ImGui::Begin("Settings");
	ImGui::Text("DrawInfor");
	ImGui::Text("Quad: %d", stats.QuadCount);
	ImGui::Text("DrawCall: %d", stats.DrawCalls);
	ImGui::Text("Vertex: %d", stats.GetQuadVertexCount());
	ImGui::Text("Index: %d", stats.GetQuadIndexCount());
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}