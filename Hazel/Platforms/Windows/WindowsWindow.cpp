#include "WindowsWindow.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "../OpenGL/OpenglGraphicsContext.h"
namespace Hazel {

	Window* Window::Create(const WindowProps props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	int WindowsWindow::GetWidth()
	{
		return mData.mWidth;
	}

	int WindowsWindow::GetHeight()
	{
		return mData.mHeight;
	}

	void WindowsWindow::OnUpdate()
	{
		glfwSwapBuffers(mGLFWWindow);
		glfwPollEvents();
	}

	void WindowsWindow::SetEventCallback(const EventCallbackFn& callback)
	{
		mData.mEventCallback = callback;
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		mData.mVSync = enabled;
	}

	bool WindowsWindow::IsVSync()
	{
		return mData.mVSync;
	}

	void* WindowsWindow::GetWindowPointer()
	{
		return mGLFWWindow;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		mData.mHeight = props.mHeith;
		mData.mWidth = props.mWidth;
		mData.mTitle = props.mTitle;

		glfwSetErrorCallback(this->error_callback);

		if (!mIsInited)
		{
			glfwInit();
			mIsInited = true;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		mGLFWWindow = glfwCreateWindow(mData.mWidth, mData.mHeight, mData.mTitle.c_str(), NULL, NULL);
		if (!mGLFWWindow)
		{
			glfwTerminate();
		}

		mGraphics = std::make_shared<OpenglGraphicsContext>(mGLFWWindow) ;

		glfwSetWindowUserPointer(mGLFWWindow, &mData);

		glfwSetWindowCloseCallback(mGLFWWindow, [](GLFWwindow* window) 
			{
				WindowCloseEvent e;
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.mEventCallback(e);
			});

		glfwSetWindowSizeCallback(mGLFWWindow, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.mHeight = height;
				data.mWidth = width;

				WindowResizeEvent e(width, height);
				data.mEventCallback(e);
			});

		glfwSetKeyCallback(mGLFWWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressEvent e(key, 0);
					data.mEventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent e(key);
					data.mEventCallback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressEvent e(key, 1);
					data.mEventCallback(e);
					break;

				}
				default:
					break;
				}
			});

		glfwSetCharCallback(mGLFWWindow, [](GLFWwindow* window, unsigned int codepoint) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypeEvent e(codepoint);
				data.mEventCallback(e);
			});

		glfwSetMouseButtonCallback(mGLFWWindow, [](GLFWwindow* window, int button, int action, int mods) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressEvent e(button);
					data.mEventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleaseEvent e(button);
					data.mEventCallback(e);
					break;
				}
				default:
					break;
				}
			});

		glfwSetScrollCallback(mGLFWWindow, [](GLFWwindow* window, double xoffset, double yoffset) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseButtonScrollEvent e(xoffset, yoffset);
				data.mEventCallback(e);

			});

		glfwSetCursorPosCallback(mGLFWWindow, [](GLFWwindow* window, double xpos, double ypos) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMoveEvent e(xpos, ypos);
				data.mEventCallback(e);
			});

		// NOTE: OpenGL error checks have been omitted for brevity

	}

	void WindowsWindow::Shutdown()
	{
		
		glfwDestroyWindow(mGLFWWindow);
	}

	void WindowsWindow::error_callback(int error, const char* description)
	{

	}

}