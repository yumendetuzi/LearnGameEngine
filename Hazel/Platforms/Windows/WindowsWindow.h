#pragma once 
#include "../../Core.h"
#include "../../Window.h"
#include "../../Render/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
	class HAZEL_API WindowsWindow :public Window
	{
	public:
		WindowsWindow(const WindowProps& );
		virtual int GetWidth();
		virtual int GetHeight();
		virtual void OnUpdate();
		virtual void SetEventCallback(const EventCallbackFn& callback);
		virtual void SetVSync(bool enabled);
		virtual bool IsVSync();
		virtual void* GetWindowPointer() override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		static void error_callback(int error, const char* description);

		struct WindowData
		{
			int mWidth, mHeight;
			bool mVSync;
			std::string mTitle;
			
			EventCallbackFn mEventCallback;
		};
		GLFWwindow* mGLFWWindow;
		std::shared_ptr<GraphicsContext> mGraphics;
		WindowData mData;
		bool mIsInited = false;
	};
}