#pragma once
#include "../../Render/VertexBuffer.h"
namespace Hazel {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vert, unsigned int size);
		~OpenGLVertexBuffer();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void SetLayout(const BufferLayout& layout) override { mLayout = layout; }
		virtual BufferLayout& GetLayout() override { return mLayout; }
	private:
		unsigned int mID;
		BufferLayout mLayout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public :
		OpenGLIndexBuffer(unsigned int* indices, unsigned int size);
		~OpenGLIndexBuffer();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual unsigned int GetCount() override { return mCount; };
	private:
		unsigned int mID;
		unsigned int mCount;
	};

	class OpenGLVertexArray :public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		virtual void Bind() override;
		virtual void UnBind() override;
		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>& vert) override;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer>& indices) override;
		virtual std::shared_ptr<IndexBuffer>& GetIndexBuffer() override;
	private:
		unsigned int mID;
		std::vector<std::shared_ptr<VertexBuffer>> mVertBuffers;
		std::shared_ptr<IndexBuffer> mIndexBuffer;
		unsigned int m_VertexBufferIndex = 0;
	};
}
