#pragma once
#include "Core.h"
#include "Events/Event.h"
#include <string>
namespace Hazel
{
	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name):mName(name){}
		virtual ~Layer(){ }
		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& e) = 0;
		std::string GetName() { return mName; }
	private:
		std::string mName;
	};
}