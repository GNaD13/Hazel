#pragma once

#include "OrthographicCamera.h"

namespace Hazel {

	class Renderer2D
	{
	public:
		static void BeginScene(const OrthographicCamera& camera);
	};

}
