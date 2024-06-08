#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "../Layer.h"


namespace Hazel
{
	class HAZEL_API ImGUILayer :public Layer
	{
	public:
		ImGUILayer(const std::string& name, void* userPointer ):Layer(name),mGlfwWindowPointer(userPointer){}
		~ImGUILayer() {};
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& e) override;

	private:
		void* mGlfwWindowPointer = nullptr;
	};
}