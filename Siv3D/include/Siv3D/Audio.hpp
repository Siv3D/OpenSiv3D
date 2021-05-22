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
# include <memory>
# include "Common.hpp"
# include "AssetHandle.hpp"

namespace s3d
{
	/// @brief オーディオ
	class Audio : public AssetHandle<Audio>
	{
	public:

		static constexpr size_t MaxBusCount = 4;

		static constexpr size_t MaxFilterCount = 8;

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Audio();
	};
}
