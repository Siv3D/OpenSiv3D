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
# include "../Common.hpp"
# include "P2Fwd.hpp"

namespace s3d
{
	/// @brief 部品 (P2Shape) の干渉フィルタ
	/// @reamark 部品 (P2Shape) にカテゴリビットフラグを指定し、特定のビットフラグを持つ部品と干渉しないようにできます。
	/// @remark 部品 A, B について ((A.maskBits & B.categoryBits) != 0) && ((B.maskBits & A.categoryBits) != 0) のときのみ干渉が発生します。
	struct P2Filter
	{
		/// @brief 自身が所属するカテゴリーを表すビットフラグです。
		uint16 categoryBits = 0b0000'0000'0000'0001;

		/// @brief 物理的に干渉する相手のカテゴリーを表すビットフラグです。
		uint16 maskBits = 0b1111'1111'1111'1111;

		/// @brief グループインデックス
		/// @remark 2 つの部品のうちいずれかのグループインデックスが 0 の場合、categoryBits と maskBits によって干渉の有無が決まります。
		/// @remark 2 つの部品の両方のグループインデックスが 非 0 で、互いに異なる場合、categoryBits と maskBits によって干渉の有無が決まります。
		/// @remark 2 つの部品のグループインデックスが 1 以上で、互いに等しい場合、必ず干渉します。
		/// @remark 2 つの部品のグループインデックスが -1 以下で、互いに等しい場合、必ず干渉しません。
		int16 groupIndex = 0;
	};
}
