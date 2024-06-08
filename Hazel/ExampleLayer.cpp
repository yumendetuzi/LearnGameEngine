#include "ExampleLayer.h"
namespace Hazel
{


	ExampleLayer::ExampleLayer(const std::string& name):Layer(name)
	{

	}

	ExampleLayer::~ExampleLayer()
	{

	}

	void ExampleLayer::OnUpdate()
	{
		//HZ_INFO("example layer update!");
	}

	void ExampleLayer::OnEvent(Event& e)
	{
		HZ_INFO("example layer onevent!");
	}

	void ExampleLayer::OnAttach()
	{

	}

	void ExampleLayer::OnDetach()
	{

	}

}