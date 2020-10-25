﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
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
	private:

		std::shared_ptr<IConstantBufferDetail> pImpl;

	public:

		SIV3D_NODISCARD_CXX20
		ConstantBufferBase() = default;

		SIV3D_NODISCARD_CXX20
		ConstantBufferBase(const ConstantBufferBase&) = default;

		SIV3D_NODISCARD_CXX20
		explicit ConstantBufferBase(size_t size);

		[[nodiscard]]
		bool _internal_update(const void* data, size_t size);

		[[nodiscard]]
		const IConstantBufferDetail* _detail() const;
	};

	/// @brief 定数バッファ（シェーダ）
	/// @tparam Type 定数バッファ用の型
	template <class Type>
	class ConstantBuffer
	{
	private:

		static_assert(sizeof(Type) <= (16 * 4096)); // <= 64KB

		static constexpr size_t _alignment = Max<size_t>(alignof(Type), 16);

		struct alignas(_alignment) WrapperType
		{
			Type data;
		};

		ConstantBufferBase m_base;

		WrapperType* const m_wrapper	= AlignedNew<WrapperType>();

		bool m_hasDirty					= true;

	public:

		static constexpr size_t Size		= sizeof(WrapperType);

		static constexpr size_t Alignment	= alignof(WrapperType);

		SIV3D_NODISCARD_CXX20
		ConstantBuffer();

		SIV3D_NODISCARD_CXX20
		explicit ConstantBuffer(const Type& data);

		~ConstantBuffer();

		[[nodiscard]]
		constexpr size_t size() const noexcept;

		[[nodiscard]]
		const float* data() const noexcept;

		[[nodiscard]]
		Type& get() noexcept;

		[[nodiscard]]
		const Type& get() const noexcept;

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
	};
}

# include "detail/ConstantBuffer.ipp"
