#pragma once
#include "Core.h"
#include "../../Render/GraphicsContext.h"

struct GLFWwindow;
namespace Hazel {
	class HAZEL_API OpenglGraphicsContext:public GraphicsContext {
	public:
		OpenglGraphicsContext(GLFWwindow* window);
		virtual ~OpenglGraphicsContext();
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* mWindow;
	};
	
}
