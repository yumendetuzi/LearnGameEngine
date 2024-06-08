#pragma once
#include <string>
#include "../Log.h"
namespace Hazel {
	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	struct BufferElement {
		std::string name;
		ShaderDataType dataType;
		unsigned int Size;
		unsigned int Offset;
		bool bNormal;

		BufferElement() = default;
		BufferElement(const std::string& name, ShaderDataType type, bool normalize = false) :
			name(name), dataType(type), Size(ShaderDataTypeSize(type)), Offset(0), bNormal(normalize)
		{

		}

		uint32_t GetComponentCount() const
		{
			switch (dataType)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3; // 3* float3
			case ShaderDataType::Mat4:    return 4; // 4* float4
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}

			HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements);
		~BufferLayout();

		std::vector<BufferElement>& GetElements() { return mElements; }
		unsigned int GetStride() const;
		std::vector<BufferElement>::iterator begin() { return mElements.begin(); }
		std::vector<BufferElement>::iterator end() { return mElements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return mElements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return mElements.end(); }


	private:
		void CalculateOffsetAndStride();

		std::vector<BufferElement> mElements;
		unsigned int mStride;
	};

	class  IndexBuffer {
	public:
		~IndexBuffer() {};
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual unsigned int GetCount() = 0;
		static IndexBuffer* CreateIndexBuffer(unsigned int* indices, unsigned int size);
	};
	class  VertexBuffer {
	public:
		~VertexBuffer() {};
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual BufferLayout& GetLayout() = 0;
		static VertexBuffer* CreateVertexBuffer(float* vert, unsigned int size);
	};


	

	class VertexArray {
	public:
		virtual ~VertexArray() {}
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>& vert) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer>& indices) = 0;
		virtual std::shared_ptr<IndexBuffer>& GetIndexBuffer() = 0;

		static VertexArray* Create();
	};
}
