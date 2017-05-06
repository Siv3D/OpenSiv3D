//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "AlignedMemory.hpp"

namespace s3d
{
	namespace detail
	{
		class ConstantBufferBase
		{
		private:

			class ConstantBufferDetail;

			std::shared_ptr<ConstantBufferDetail> m_detail;

		public:

			explicit ConstantBufferBase(size_t size);

			bool _internal_update(const void* data, size_t size);

			const ConstantBufferDetail* _detail() const;
		};
	}

	template <class Type>
	class ConstantBuffer
	{
	private:

		static constexpr size_t Size = sizeof(Type);

		static_assert(Size <= 16 * 4096); // <= 64KB

		static_assert(Size % 16 == 0);

		detail::ConstantBufferBase m_base;

		Type* const m_data = AlignedMalloc<Type>();

	public:

		static const char* Name()
		{
			return Type::Name();
		}

		static constexpr uint32 BindingPoint()
		{
			return Type::BindingPoint();
		}

		ConstantBuffer()
			: m_base(Size)
		{
			
		}

		explicit ConstantBuffer(const Type& data)
			: ConstantBuffer()
		{
			*m_data = data;
		}

		~ConstantBuffer()
		{
			AlignedFree(m_data);
		}

		constexpr size_t getDataSize() const noexcept
		{
			return Size;
		}

		const float* getPtr() const
		{
			return static_cast<const float*>(static_cast<const void*>(m_data));
		}

		Type& get()
		{
			return *m_data;
		}

		const Type& get() const
		{
			return *m_data;
		}

		bool _internal_update()
		{
			return m_base._internal_update(m_data, Size);
		}

		const detail::ConstantBufferBase& base() const
		{
			return m_base;
		}

		Type& operator *()
		{
			return *m_data;
		}

		const Type& operator *() const
		{
			return *m_data;
		}

		Type* operator ->()
		{
			return m_data;
		}

		const Type* operator ->() const
		{
			return *m_data;
		}
	};
}
