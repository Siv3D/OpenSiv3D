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
# include "Common.hpp"
# include "Array.hpp"
# include "AssetState.hpp"

namespace s3d
{
	/// @brief アセット名
	using AssetName = String;

	using AssetNameView = StringView;

	/// @brief アセットタグ名
	using AssetTag = String;

	struct AssetNameAndTags
	{
		AssetName name;

		Array<AssetTag> tags;
	};

	/// @brief アセットの状態
	struct AssetInfo
	{
		/// @brief アセットのロード状況
		AssetState state;

		/// @brief タグ
		Array<AssetTag> tags;
	};
}
