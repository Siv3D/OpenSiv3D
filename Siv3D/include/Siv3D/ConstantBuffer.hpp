//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "Memory.hpp"
# include "Utility.hpp"

namespace s3d
{
	class IConstantBufferDetail;

	/// @brief 定数バッファ（シェーダ）ベース
	class ConstantBufferBase
	{
	public:

		SIV3D_NODISCARD_CXX20
		ConstantBufferBase() = default;

		SIV3D_NODISCARD_CXX20
		ConstantBufferBase(const ConstantBufferBase&) = default;

		SIV3D_NODISCARD_CXX20
		explicit ConstantBufferBase(size_t size);

		bool _internal_update(const void* data, size_t size);

		[[nodiscard]]
		const IConstantBufferDetail* _detail() const;
	
	private:

		std::shared_ptr<IConstantBufferDetail> pImpl;
	};

	/// @brief 定数バッファ（シェーダ）
	/// @tparam Type 定数バッファ用の型
	template <class Type>
	class ConstantBuffer
	{
	public:

		static_assert(sizeof(Type) <= (16 * 4096)); // <= 64KB

		static_assert(std::is_trivially_copyable_v<Type>);

		static constexpr size_t _alignment = Max<size_t>(alignof(Type), 16);

	SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4324)

		struct alignas(_alignment) WrapperType
		{
			Type data;
		};

	SIV3D_DISABLE_MSVC_WARNINGS_POP()

		static constexpr size_t Size		= sizeof(WrapperType);

		static constexpr size_t NumVectors	= (Size / 16);

		static constexpr size_t Alignment	= alignof(WrapperType);

		SIV3D_NODISCARD_CXX20
		ConstantBuffer();

		SIV3D_NODISCARD_CXX20
		ConstantBuffer(const Type& data);

		~ConstantBuffer();

		ConstantBuffer& operator =(const Type& data);

		[[nodiscard]]
		constexpr size_t size() const noexcept;

		[[nodiscard]]
		const float* data() const noexcept;

		[[nodiscard]]
		Type& get() noexcept;

		[[nodiscard]]
		const Type& get() const noexcept;

		[[nodiscard]]
		bool isDirty() const noexcept;

		bool _update_if_dirty();

		[[nodiscard]]
		const ConstantBufferBase& base() const noexcept;

		[[nodiscard]]
		Type& operator *() noexcept;

		[[nodiscard]]
		const Type& operator *() const noexcept;

		[[nodiscard]]
		Type* operator ->() noexcept;

		[[nodiscard]]
		const Type* operator ->() const noexcept;

	private:

		ConstantBufferBase m_base;

		WrapperType* const m_wrapper = AlignedNew<WrapperType>();

		bool m_hasDirty = true;
	};
}

# include "detail/ConstantBuffer.ipp"
