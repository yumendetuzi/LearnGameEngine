#include "OpenGLBuffer.h"
#include <glad/glad.h>
namespace Hazel {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vert, unsigned int size):mID(0)
	{
		glGenBuffers(1, &mID);
		glBindBuffer(GL_ARRAY_BUFFER, mID);
		glBufferData(GL_ARRAY_BUFFER, size, vert, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &mID);

	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, mID);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int size) :mID(0)
	{
		glGenBuffers(1, &mID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * size, indices, GL_STATIC_DRAW);
		mCount = size;
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &mID);
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
	}

	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &mID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &mID);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(mID);
	}

	void OpenGLVertexArray::UnBind()
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& vert)
	{
		HZ_CORE_ASSERT(vert->GetLayout().GetElements().size(), "vertex buffer has no layout!");
		glBindVertexArray(mID);
		vert->Bind();

		const auto& layout = vert->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.dataType)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.dataType),
					element.bNormal ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribIPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.dataType),
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						count,
						ShaderDataTypeToOpenGLBaseType(element.dataType),
						element.bNormal ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(element.Offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_VertexBufferIndex, 1);
					m_VertexBufferIndex++;
				}
				break;
			}
			default:
				HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
		}

		mVertBuffers.push_back(vert);
	}

	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer>& indices)
	{
		glBindVertexArray(mID);
		indices->Bind();
		mIndexBuffer = indices;
	}

	std::shared_ptr<Hazel::IndexBuffer>& OpenGLVertexArray::GetIndexBuffer()
	{
		return mIndexBuffer;
	}

}

