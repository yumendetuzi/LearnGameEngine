#include <Hazel.h>
#include <stdio.h>

class SandBox : public Hazel::Application {
public:
	SandBox();
	~SandBox();
	bool TestEvent();
};

SandBox::SandBox()
{
	Application::PushLayer(new Hazel::ExampleLayer("ExampleLayer"));
	Application::PushLayer(new Hazel::ImGUILayer("ImGUILayer", Application::GetWindow().GetWindowPointer()));
}

SandBox::~SandBox()
{

}


bool SandBox::TestEvent()
{
	return false;
}

Hazel::Application* Hazel::CreateApplication()
{
	return new SandBox();
}