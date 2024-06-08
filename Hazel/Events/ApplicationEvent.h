#pragma once
#include "Event.h"

namespace Hazel {
	class HAZEL_API WindowResizeEvent :public Event
	{
	public:
		WindowResizeEvent(int width, int height):mWidth(width), mHeight(height) {}
		std::string ToString() override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << mWidth << "," << mHeight;
			return ss.str();
		}
		int GetWidth() { return mWidth; }
		int GetHeight() { return mHeight; }
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CATEGORY_FLAG(EventCategoryApplication)
	private:
		int mWidth, mHeight;
	};

	class HAZEL_API WindowCloseEvent :public Event
	{
	public:
		WindowCloseEvent() {}
		std::string ToString() override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CATEGORY_FLAG(EventCategoryApplication)
	};

	class HAZEL_API AppTickEvent :public Event
	{
	public:
		AppTickEvent() {}
		std::string ToString() override
		{
			std::stringstream ss;
			ss << "AppTickEvent";
			return ss.str();
		}
		EVENT_CLASS_TYPE(AppTick)
		EVENT_CATEGORY_FLAG(EventCategoryApplication)
	};

	class HAZEL_API AppUpdateEvent :public Event
	{
	public:
		AppUpdateEvent() {}
		std::string ToString() override
		{
			std::stringstream ss;
			ss << "AppUpdateEvent";
			return ss.str();
		}
		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CATEGORY_FLAG(EventCategoryApplication)
	};

	class HAZEL_API AppRenderEvent :public Event
	{
	public:
		AppRenderEvent() {}
		std::string ToString() override
		{
			std::stringstream ss;
			ss << "AppRenderEvent";
			return ss.str();
		}
		EVENT_CLASS_TYPE(AppRender)
			EVENT_CATEGORY_FLAG(EventCategoryApplication)
	};

}