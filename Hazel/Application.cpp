#include "Application.h"
#include <stdio.h>
#include "Events/KeyEvent.h"
Hazel::Application::Application()
{

}

Hazel::Application::~Application()
{

}

void Hazel::Application::Run()
{
	Hazel::KeyPressEvent keyP(1, 1);
	Hazel::EventDispatcher e(keyP);

	printf("Application Run()\n");
}
