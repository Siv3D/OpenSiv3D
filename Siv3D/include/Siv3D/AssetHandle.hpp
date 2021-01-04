//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "AssetIDWrapper.hpp"

namespace s3d
{
	template <class AssetType>
	struct AssetHandle
	{
	public:

		using AssetIDWrapperType = AssetIDWrapper<AssetHandle>;

		using IDType = typename AssetIDWrapperType::IDType;

		SIV3D_NODISCARD_CXX20
		AssetHandle();

		SIV3D_NODISCARD_CXX20
		explicit AssetHandle(std::shared_ptr<AssetIDWrapperType>&& id);

		[[nodiscard]]
		IDType id() const noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		bool operator ==(const AssetHandle& other) const noexcept;

		[[nodiscard]]
		bool operator !=(const AssetHandle& other) const noexcept;

		void release();

	protected:

		std::shared_ptr<AssetIDWrapperType> m_handle;
	};
}

# include "detail/AssetHandle.ipp"
