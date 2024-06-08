#include "OpenglGraphicsContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../Log.h"
namespace Hazel {

	
	OpenglGraphicsContext::OpenglGraphicsContext(GLFWwindow* window):mWindow(window)
	{
		Init();
	}

	OpenglGraphicsContext::~OpenglGraphicsContext()
	{

	}

	void OpenglGraphicsContext::Init()
	{

		glfwMakeContextCurrent(mWindow);

		int state = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		//state = gladLoadGL();
		HZ_CORE_ASSERT(state, "Init glad fail!");
		glfwSwapInterval(1);

		HZ_CORE_INFO("OpenGL 信息:");
		HZ_CORE_INFO("	Vendor：{0}", (const char*)glGetString(GL_VENDOR));
		HZ_CORE_INFO("	显卡名：{0}", (const char*)glGetString(GL_RENDERER));
		HZ_CORE_INFO("	版本：{0}", (const char*)glGetString(GL_VERSION));

	}

	void OpenglGraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(mWindow);
	}

}