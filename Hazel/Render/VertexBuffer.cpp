#include "VertexBuffer.h"
#include "../Platforms/OpenGL/OpenGLBuffer.h"
#include "../Render/Renderer.h"
namespace Hazel {

	IndexBuffer* IndexBuffer::CreateIndexBuffer(unsigned int* indices, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None:
		case RenderAPI::OpenGL:
		default:
			return new OpenGLIndexBuffer(indices, size);
		}
	}

	VertexBuffer* VertexBuffer::CreateVertexBuffer(float* vert, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None:
		case RenderAPI::OpenGL:
		default:
			return new OpenGLVertexBuffer(vert, size);
		}
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements):mElements(elements)
	{
		CalculateOffsetAndStride();
	}

	BufferLayout::~BufferLayout()
	{

	}

	unsigned int BufferLayout::GetStride() const
	{
		return mStride;
	}

	void BufferLayout::CalculateOffsetAndStride()
	{
		int offset = 0;
		mStride = 0;
		for each (auto var in mElements)
		{
			var.Offset = offset;
			offset += var.Size;
			mStride += var.Size;
		}
	}

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None:
		case RenderAPI::OpenGL:
		default:
			return new OpenGLVertexArray();
		}
	}

}

