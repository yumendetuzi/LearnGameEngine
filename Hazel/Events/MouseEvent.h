#pragma once
#include "Event.h"
#include <sstream>

namespace Hazel {
	class HAZEL_API MouseMoveEvent:public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CATEGORY_FLAG(EventCategoryInput | EventCategoryMouse)

		MouseMoveEvent(int x, int y):mX(x), mY(y){}
		virtual std::string ToString()
		{
			std::stringstream ss;
			ss << "MouseMoveEvent: " << mX << "," << mY;
			return ss.str();
		}
		int GetX() { return mX; }
		int GetY() { return mY; }
	protected:
	private:
		int mX, mY;
	};

	class HAZEL_API MouseButtonEvent :public Event
	{
	public:
		EVENT_CATEGORY_FLAG(EventCategoryInput | EventCategoryMouse)

		int GetMouseButton() { return mButton; }
	protected:
		MouseButtonEvent(int button) :mButton(button) {}

	protected:
		int mButton;
	};

	class HAZEL_API MouseButtonPressEvent :public MouseButtonEvent
	{
	public:
		EVENT_CLASS_TYPE(MouseButtonPressed)

		MouseButtonPressEvent(int button) :MouseButtonEvent(button) {}

		virtual std::string ToString()
		{
			std::stringstream ss;
			ss << "MouseButtonPressEvent: " << mButton ;
			return ss.str();
		}
	};

	class HAZEL_API MouseButtonReleaseEvent :public MouseButtonEvent
	{
	public:
		EVENT_CLASS_TYPE(MouseButtonRelease)

			MouseButtonReleaseEvent(int button) :MouseButtonEvent(button) {}

		virtual std::string ToString()
		{
			std::stringstream ss;
			ss << "MouseButtonReleaseEvent: " << mButton;
			return ss.str();
		}
	};

	class HAZEL_API MouseButtonScrollEvent :public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CATEGORY_FLAG(EventCategoryInput | EventCategoryMouse)

		MouseButtonScrollEvent(float x, float y) :mX(x), mY(y) {}
		virtual std::string ToString()
		{
			std::stringstream ss;
			ss << "MouseButtonScrollEvent: " << mX << "," << mY;
			return ss.str();
		}
		float GetX() { return mX; }
		float GetY() { return mY; }
	protected:
	private:
		float mX, mY;
	};
}