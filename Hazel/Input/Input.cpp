#include "Input.h"
#include "../Application.h"
#include <GLFW/glfw3.h>
namespace Hazel
{
	class HAZEL_API WindowsInput :public Input
	{
	public:
		WindowsInput();
		virtual ~WindowsInput();
		virtual void Init() override;
		virtual bool GetKey(int code) override;
		virtual bool GetMouseButton(int button) override;
		virtual std::pair<float, float> GetMousePosition() override;
	};

	
	WindowsInput::WindowsInput()
	{

	}

	WindowsInput::~WindowsInput()
	{

	}

	void WindowsInput::Init()
	{

	}

	bool WindowsInput::GetKey(int code)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetWindowPointer());
		return glfwGetKey(window, code);
	}

	bool WindowsInput::GetMouseButton(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetWindowPointer());
		return glfwGetMouseButton(window, button);
	}

	std::pair<float, float> WindowsInput::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetWindowPointer());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { x, y };
	}

	Hazel::Input* Input::GetInput()
	{
		static WindowsInput s_instance;
		return &s_instance;
	}

}