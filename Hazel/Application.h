#pragma once
#include "Core.h"
#include "Window.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Render/VertexBuffer.h"
#include "Events/ApplicationEvent.h"

namespace Hazel {
	class HAZEL_API Application {
	public:
		 Application();
		virtual ~Application();
		virtual void Run();
		virtual void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		bool OnWindowClose(WindowCloseEvent& e);

		Window& GetWindow() { return *mWindow; }
		static inline Application& GetApp() { return *sInstance; }


	private:
		std::unique_ptr<Window> mWindow;
		LayerStack mLayerStack;
		static Application* sInstance;
		bool mIsRuning;
		std::shared_ptr<VertexArray> mVertArr;
	};
	
	Application* CreateApplication();
}
