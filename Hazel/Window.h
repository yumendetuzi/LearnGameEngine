#pragma once
#include "Core.h"
#include <string>
#include <functional>
#include "Events/Event.h"
namespace Hazel {
	struct HAZEL_API WindowProps
	{
		WindowProps():mWidth(1280),mHeith(720),mTitle("Hazel Engine") {}
		int mWidth, mHeith;
		std::string mTitle;
	}; 

	class HAZEL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		Window() {};
		virtual ~Window() {};
		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
		virtual void OnUpdate() = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() = 0;
		virtual void* GetWindowPointer() = 0;
		static Window* Create(const WindowProps props = WindowProps());
	private:
		WindowProps mProps;
		void* mPHandle = nullptr;
	};
}
