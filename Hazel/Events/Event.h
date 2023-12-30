#pragma once
#include "../Core.h"
#include <string>
#include <ostream>

namespace Hazel {
	enum class EventType
	{
		None = 0,WindowClose,WindowResize,WindowFocus,WindoLostFocus,WindowMoved,
		AppTick,AppUpdate,AppRender,
		KeyPressed,KeyReleased,Keytyped,
		MouseButtonPressed, MouseButtonRelease,MouseMoved,MouseScrolled
	};

	enum EventGategory
	{
		None = 0,
		EventCategoryApplication	= BIT(1),
		EventCategoryInput			= BIT(2),
		EventCategoryKeyboard		= BIT(3),
		EventCategoryMouse			= BIT(4),
		EventCateGoryMouseButton	= BIT(5)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){ return EventType::##type;}\
								virtual EventType GetEventType(){ return GetStaticType();}\
								virtual const char* GetName(){	return #type;}
#define EVENT_CATEGORY_FLAG(category) virtual int GetEventCategoryFlag(){ return category;}

	class HAZEL_API Event {
	public:
		bool mHandle = false;
		virtual const char* GetName() = 0;
		virtual EventType GetEventType() = 0;
		virtual int GetEventCategoryFlag() = 0;
		virtual std::string ToString() { return GetName(); }

		bool IsGategory(EventGategory category)
		{
			return category & GetEventCategoryFlag();
		}

	};


	class HAZEL_API EventDispatcher {
	public:
		template<typename T>
		using EventFn = std::function<bool(&T)>;

		EventDispatcher(Event& event) :mEvent(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (mEvent.GetEventType() == T::GetStaticType())
			{
				mEvent.mHandle = func(*(T*)&mEvent);
				return true;
			}
			return false;
		}

	private:
		Event& mEvent;
	};


	inline std::ostream& operator<<(std::ostream& os, Event& e) {
		return os << e.ToString();
	}
}