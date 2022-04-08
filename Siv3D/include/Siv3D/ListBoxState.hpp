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
# include "String.hpp"
# include "Optional.hpp"

namespace s3d
{
	/// @brief リストボックスの状態
	struct ListBoxState
	{
		/// @brief アイテム
		Array<String> items;

		/// @brief 選択されているアイテムのインデックス
		Optional<size_t> selectedItemIndex;

		/// @brief スクロールバーの状態
		Optional<std::pair<int32, double>> scrollBarGrabbed;

		/// @brief スクロール数
		int32 scroll = 0;

		/// @brief ホイールの状態
		double wheel = 0.0;

		SIV3D_NODISCARD_CXX20
		ListBoxState() = default;

		SIV3D_NODISCARD_CXX20
		explicit ListBoxState(const Array<String>& _items);

		SIV3D_NODISCARD_CXX20
		explicit ListBoxState(Array<String>&& _items) noexcept;
	};
}

# include "detail/ListBoxState.ipp"
