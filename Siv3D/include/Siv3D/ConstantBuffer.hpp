//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
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

		bool m_hasDirty = false;

		bool update()
		{
			return m_base._internal_update(m_data, Size);
		}

	public:

		[[nodiscard]] static const char* Name()
		{
			return Type::Name();
		}

		[[nodiscard]] static constexpr uint32 BindingPoint()
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

		[[nodiscard]] constexpr size_t getDataSize() const noexcept
		{
			return Size;
		}

		[[nodiscard]] const float* getPtr() const
		{
			return static_cast<const float*>(static_cast<const void*>(m_data));
		}

		[[nodiscard]] Type& get()
		{
			m_hasDirty = true;
			return *m_data;
		}

		[[nodiscard]] const Type& get() const
		{
			return *m_data;
		}

		bool _update_if_dirty()
		{
			if (!m_hasDirty)
			{
				return true;
			}

			return update();
		}

		[[nodiscard]] const detail::ConstantBufferBase& base() const
		{
			return m_base;
		}

		[[nodiscard]] Type& operator *()
		{
			m_hasDirty = true;
			return *m_data;
		}

		[[nodiscard]] const Type& operator *() const
		{
			return *m_data;
		}

		[[nodiscard]] Type* operator ->()
		{
			m_hasDirty = true;
			return m_data;
		}

		[[nodiscard]] const Type* operator ->() const
		{
			return *m_data;
		}
	};
}
