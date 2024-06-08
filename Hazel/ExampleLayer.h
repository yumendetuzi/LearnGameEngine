#pragma once
#include "Core.h"
#include "Layer.h"
#include "Log.h"
#include "Events/Event.h"
#include <string>
namespace Hazel
{
	class HAZEL_API ExampleLayer:public Layer
	{
	public:
		ExampleLayer(const std::string& name);
		virtual ~ExampleLayer(); 
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& e) override; 
		virtual void OnAttach() override;
		virtual void OnDetach() override;

	};
}