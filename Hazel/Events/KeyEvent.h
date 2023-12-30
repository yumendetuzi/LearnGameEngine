#pragma once
#include "Event.h"
#include <sstream>

namespace Hazel {
	class HAZEL_API KeyEvent :public Event {
	public:
		EVENT_CATEGORY_FLAG(EventCategoryInput | EventCategoryKeyboard)

		int GetKeyCode() { return mKeyCode; }

		KeyEvent(){}
		KeyEvent(int keycode):mKeyCode(keycode){

		}
		virtual ~KeyEvent(){}
	protected:
		int mKeyCode;
	};

	class HAZEL_API KeyPressEvent :public KeyEvent
	{
	public:
		EVENT_CLASS_TYPE(KeyPressed)

		KeyPressEvent(int keycode, int repeatcount):KeyEvent(keycode), mRepeatCount(repeatcount){}

		inline int GetRepeatCount() { return mRepeatCount; }
		virtual std::string ToString() override
		{
			std::stringstream ss;
			ss << "KeyPressEvent: " << mKeyCode;
			return ss.str();
		}

	protected:
		int mRepeatCount;
	};

	class HAZEL_API KeyReleaseEvent :public KeyEvent
	{
	public:
		EVENT_CLASS_TYPE(KeyReleased)

		KeyReleaseEvent(int keycode) :KeyEvent(keycode){}

		virtual std::string ToString() override
		{
			std::stringstream ss;
			ss << "KeyReleaseEvent: " << mKeyCode;
			return ss.str();
		}
	};

	class HAZEL_API KeyTypeEvent :public KeyEvent
	{
	public:
		EVENT_CLASS_TYPE(Keytyped)
		KeyTypeEvent(int keycode) :KeyEvent(keycode) {}

		virtual std::string ToString() override
		{
			std::stringstream ss;
			ss << "KeyTypeEvent: " << mKeyCode;
			return ss.str();
		}
	};

}