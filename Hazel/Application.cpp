#include "Application.h"
#include <stdio.h>
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Input/Input.h"
#include "Render/Shader.h"
#include <glad/glad.h>
//#include <iostream>
//#include <filesystem>
//void GLClearError()
//{
//	while (glGetError() != GL_NO_ERROR);
//}
//
//bool GLCallLog(const char* function, const char* file, int line)
//{
//	GLenum error;
//	while ((error = glGetError()) != GL_NO_ERROR)
//	{
//		std::cout << "[OpenGL Error] (" << std::hex << error << ") ";
//		std::cout << std::dec << function << "," << file << "," << line << std::endl;
//		return false;
//	}
//	return true;
//}
//#define GLCALL(x)   GLClearError();\
//                    x;\
//                    HZ_CORE_ASSERT(GLCallLog(#x, __FILE__, __LINE__)) ;

namespace Hazel {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::sInstance = NULL;
	Application::Application()
	{
		sInstance = this;
		mWindow = std::unique_ptr<Window>(Window::Create());
		mWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));
		mIsRuning = true;
	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		HZ_INFO("Application Run()\n");

		// 0.顶点数据
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		unsigned int indices[3] = { 0, 1, 2 }; // 索引数据

		std::shared_ptr<VertexBuffer> vertex;
		vertex.reset(VertexBuffer::CreateVertexBuffer(vertices, sizeof(vertices)));
		{
			BufferLayout bufferLayout = { {"a_position", ShaderDataType::Float3},
			{"a_color", ShaderDataType::Float4} };
			vertex->SetLayout(bufferLayout);
		}
		std::shared_ptr<IndexBuffer> index;
		index.reset(IndexBuffer::CreateIndexBuffer(indices, sizeof(indices)/sizeof(unsigned int)));
		

		mVertArr.reset(VertexArray::Create());
		mVertArr->AddVertexBuffer(vertex);
		mVertArr->SetIndexBuffer(index);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		std::shared_ptr<Shader> shader;
		shader.reset(new Shader(vertexSrc, fragmentSrc));

		while (mIsRuning)
		{
			for (std::vector<Layer*>::iterator it = mLayerStack.Begin(); it < mLayerStack.End(); it++)
			{
				(*it)->OnUpdate();
			}

			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->Bind();
			mVertArr->Bind();

			/*GLCALL*/(glDrawElements(GL_TRIANGLES, mVertArr->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, NULL));
			
			mWindow->OnUpdate();

			//auto pos = Input::GetInput()->GetMousePosition();
			//HZ_INFO("{0}, {1}",pos.first, pos.second);

			//HZ_INFO("{0}, {1}", "key is press", Input::GetInput()->GetKey(HAZEL_KEY_B));
			//HZ_INFO("{0}, {1}", "mouse is press", Input::GetInput()->GetMouseButton(HAZEL_MOUSE_BUTTON_LEFT));

		}
	}

	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (std::vector<Layer*>::iterator it = mLayerStack.End(); it < mLayerStack.Begin(); it--)
		{
			(*it)->OnEvent(e);
			if (e.mHandle)	
			{
				break;//已被当前层处理，停止往下传
			}
		}

	}

	void Application::PushLayer(Layer* layer)
	{
		mLayerStack.PushLayer(layer);
		layer->OnAttach();

	}

	void Application::PopLayer(Layer* layer)
	{
		mLayerStack.PopLayer(layer);
		layer->OnDetach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		mIsRuning = false;
		return true;
	}

}
