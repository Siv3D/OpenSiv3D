//-----------------------------------------------
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
# include "Common.hpp"
# include "AssetID.hpp"

namespace s3d
{
	template <class AssetTag>
	class AssetIDWrapper
	{
	private:

		AssetID<AssetTag> m_id;

	public:

		using IDType = AssetID<AssetTag>;

		SIV3D_NODISCARD_CXX20
		AssetIDWrapper();

		SIV3D_NODISCARD_CXX20
		explicit AssetIDWrapper(IDType id) noexcept;

		~AssetIDWrapper();

		[[nodiscard]]
		constexpr IDType id() const noexcept;
	};
}

# include "detail/AssetIDWrapper.ipp"
