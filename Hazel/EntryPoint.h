#pragma once

extern Hazel::Application* Hazel::CreateApplication();
void main()
{
	Hazel::Log::Init();

   auto app = Hazel::CreateApplication();
   app->Run();
   delete app;
}