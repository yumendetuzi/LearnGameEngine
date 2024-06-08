#pragma once
#include <string>
namespace Hazel {
	enum class RenderAPI
	{
		None = 0,
		OpenGL,
	};

	class Renderer
	{
	public:
		inline static RenderAPI& GetAPI() { return sAPI; }
	private:
		static RenderAPI sAPI;
	};
}
