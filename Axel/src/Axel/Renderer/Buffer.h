#pragma once

namespace Axel {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t shaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case Axel::ShaderDataType::None:		return 0;
		case Axel::ShaderDataType::Float:		return 4;
		case Axel::ShaderDataType::Float2:		return 4 * 2;
		case Axel::ShaderDataType::Float3:		return 4 * 3;
		case Axel::ShaderDataType::Float4:		return 4 * 4;
		case Axel::ShaderDataType::Mat3:		return 4 * 3 * 3;
		case Axel::ShaderDataType::Mat4:		return 4 * 4 * 4;
		case Axel::ShaderDataType::Int:			return 4;
		case Axel::ShaderDataType::Int2:		return 4 * 2;
		case Axel::ShaderDataType::Int3:		return 4 * 3;
		case Axel::ShaderDataType::Int4:		return 4 * 4;
		case Axel::ShaderDataType::Bool:		return 1;
		}

		AX_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		bool normalized;

		BufferElement(ShaderDataType t_type, const std::string& t_name, bool t_normalized = false)
			: name(t_name), type(t_type), size(shaderDataTypeSize(t_type)), offset(0), normalized(t_normalized)
		{}

		uint32_t getComponentCount() const {
			switch (type)
			{
			case Axel::ShaderDataType::None:		return 0;
			case Axel::ShaderDataType::Float:		return 1;
			case Axel::ShaderDataType::Float2:		return 2;
			case Axel::ShaderDataType::Float3:		return 3;
			case Axel::ShaderDataType::Float4:		return 4;
			case Axel::ShaderDataType::Mat3:		return 3 * 3;
			case Axel::ShaderDataType::Mat4:		return 4 * 4;
			case Axel::ShaderDataType::Int:			return 1;
			case Axel::ShaderDataType::Int2:		return 2;
			case Axel::ShaderDataType::Int3:		return 3;
			case Axel::ShaderDataType::Int4:		return 4;
			case Axel::ShaderDataType::Bool:		return 1;
			}

			AX_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& t_elements) 
			: m_elements(t_elements)
		{
			calculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement>& getElements() const { return m_elements; }
		inline uint32_t getStride() const { return m_stride; }

		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
	private:
		void calculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_stride = 0;
			for (auto& e : m_elements) {
				e.offset = offset;
				offset += e.size;
				m_stride += e.size;
			}
		}
	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride = 0;
	};


	class VertexBuffer {
	public:
		VertexBuffer() = default;
		virtual ~VertexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& getLayout() const = 0;

		static VertexBuffer* create(float* verticies, uint32_t size);
	};

	class IndexBuffer {
	public:
		IndexBuffer() = default;
		virtual ~IndexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t getCount() const = 0;

		static ref<IndexBuffer> create(uint32_t* indices, uint32_t count);
	};

}