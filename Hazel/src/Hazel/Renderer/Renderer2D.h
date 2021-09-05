#pragma once

#include "OrthographicCamera.h"
<<<<<<< HEAD
=======
#include "Texture.h"
>>>>>>> 16f65513c7c1a54fa0b9ef440430c50b9252c41d

namespace Hazel {

	class Renderer2D
	{
	public:
<<<<<<< HEAD
		static void BeginScene(const OrthographicCamera& camera);
=======
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
>>>>>>> 16f65513c7c1a54fa0b9ef440430c50b9252c41d
	};

}
